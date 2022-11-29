use libc::{c_float, c_int};
use sdl2::{sys::SDL_Color, render::WindowCanvas};

use crate::{vec4_calc::{Vector4, calc_dp, calc_unit_v, calc_p_to_v, calc_vect_to_point}, object::{World, ObjectType}, ray::{Ray, normal, trace_ray}, refraction::get_refract_ray, reflection::get_reflect_ray};

pub fn fresnel(n1: c_float, n2: c_int, n: Vector4, v: Vector4) -> c_float
{
	let n2t = (n2 as f32) / 1000000.;
	let mut r0 = (n1 - n2t) / (n1 + n2t);
	r0 *= r0;
	let mut c1 = -calc_dp(n, v) as f32;
	if n1 > n2t
	{
		let ret = n1 / n2t;
		let x = ret * ret * (1. - c1 * c1);
		if x > 1. {
			return 1.;
    }
		c1 = (1. - x).sqrt();
	}
	let x = 1. - c1;
	
	r0 + (1. - r0) * x * x * x * x * x
}

pub fn fresnel_effect(obj: &mut World, ray: Ray, depth: usize /*, ren: & mut WindowCanvas*/, d: &mut f32) -> SDL_Color
{
	let mut n = Ray::default();
	n.sc = calc_vect_to_point(ray.sc, ray.v, *d);
	n.v = if obj.objects[obj.i].r#type == ObjectType::Cylinder || obj.objects[obj.i].r#type == ObjectType::Cone {
		normal(obj.objects[obj.i], *d, ray)
	}
	else {
		calc_unit_v(calc_p_to_v(obj.objects[obj.i].c, n.sc))
	};
	let mut f = fresnel(1.000293, obj.objects[obj.i].refract, n.v, ray.v);
	if f == 1. {
		return trace_ray(obj, ray, depth + 1/*, ren*/, d);
	}
		f = f * obj.objects[obj.i].reflect;
		let rfl = trace_ray(obj, get_reflect_ray(obj.objects[obj.i], ray, *d),
				depth + 1/*, ren*/, d);
		let mut rfr = trace_ray(obj, get_refract_ray(obj.objects[obj.i], ray, *d),
				depth + 1/*, ren*/, d);
		rfr = SDL_Color{r: (rfl.r as f32 * f + rfr.r as f32 * (1. - f)) as u8, g: (rfl.g as f32 * f + rfr.g as f32 *
			(1. - f)) as u8, b: (rfl.b as f32 * f + rfr.b as f32 * (1. - f)) as u8, a: 255};
	rfr
}
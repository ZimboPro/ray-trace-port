use std::{ops::{Shr}};

use libc::{c_float};
use sdl2::{sys::SDL_Color, render::WindowCanvas};

use crate::{ray::{Ray, intersection}, object::{ObjectType, World}, vec4_calc::{calc_unit_v, calc_p_to_vec, calc_multi, Vector4, calc_addition, calc_m, calc_p_dist_vec, calc_dp}, circle::{color_circle, cartoon_circle}, plane::cartoon_plane, cone::cartoon_cone, cylinder::cartoon_cylinder};
use crate::cylinder::color_cylinder;
use crate::cone::color_cone;
use crate::plane::color_plane;
pub const AMB: f32 = 0.2;

trait Init {
    fn init() -> Self;
}

impl Init for SDL_Color {
    fn init() -> Self {
        SDL_Color {
            r: 0,
            g: 0,
            b: 0,
            a: 255
        }
    }
}

pub fn init_color() -> SDL_Color {
    SDL_Color::init()
}

pub fn blend_colours(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
    // a.overlay(b)
}

pub fn dim_color(a: &SDL_Color, d: f32) -> SDL_Color {
    SDL_Color {
        r: (a.r as f32 * d) as u8,
        g: (a.g as f32 * d) as u8,
        b: (a.b as f32 * d) as u8,
        a: 255,
    }
}

pub fn mix_color(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
}

pub fn convert_str_to_color(s: String, vec: &mut SDL_Color) {
    let points: Vec<&str> = s.split(' ').collect();
    vec.r = points.first().unwrap().parse::<u8>().unwrap();
    vec.g = points.get(1).unwrap().parse::<u8>().unwrap();
    vec.b = points.get(2).unwrap().parse::<u8>().unwrap(); 
}
pub fn color_adjust(mut a: SDL_Color, mut d: c_float) -> SDL_Color {
    d *= 100.;
    let mut s: u16 = d as u16;
    s *= a.r as u16;
    a.r = (s / 100) as u8;
    let mut s: u16 = d as u16;
    s *= a.g as u16;
    a.g = (s / 100) as u8;
    let mut s: u16 = d as u16;
    s *= a.b as u16;
    a.b = (s / 100) as u8;
	a
}

pub fn get_color(obj: &mut World/*, ren: &mut WindowCanvas*/, i: usize, ry: Ray, d: &mut f32) -> SDL_Color
{
	// miss(ren);
	return if obj.objects[i].r#type == ObjectType::Circle {
		color_circle(obj, i, ry, d)
	} else if obj.objects[i].r#type == ObjectType::Cylinder {
		color_cylinder(obj, i, ry, d)
	} else if obj.objects[i].r#type == ObjectType::Cone {
		color_cone(obj, i, ry, d)
	} else {
		color_plane(obj, i, ry, d)
	}
}

pub fn get_cartoon_color(obj: &mut World/*, ren: &mut WindowCanvas*/, i: usize, ry: Ray, d: &mut f32) -> SDL_Color
{
	// miss(ren);
	return if obj.objects[i].r#type == ObjectType::Circle {
		cartoon_circle(obj, i, ry, d)
	} else if obj.objects[i].r#type == ObjectType::Cylinder {
		cartoon_cylinder(obj, i, ry, d)
	} else if obj.objects[i].r#type == ObjectType::Cone {
		cartoon_cone(obj, i, ry, d)
	} else {
		cartoon_plane(obj, i, ry, d)
	}
}

pub fn blinn_phong(obj:& mut World, n: Ray, i: usize, v: Vector4, d: &mut f32) -> SDL_Color
{
	let mut k = 0;
	let mut j = 0.;
	let mut co = obj.objects[i].col;
	while k < obj.light
	{
		let mut tmp = 1.;
		let mut l = calc_unit_v(calc_p_to_vec(n.sc, obj.lights[k].c));
		l = calc_addition(l, calc_multi(calc_unit_v(v), -1.));
		if calc_m(l) != 0.
		{
			l = calc_unit_v(l);
			tmp = calc_dp(l, n.v);
			if obj.objects[i].r#type != ObjectType::Plane && tmp < 0. {
		tmp = 0.;
			}
	   else if intersection(obj, d, calc_unit_v(calc_p_to_vec(n.sc,
		  obj.lights[k].c)), n.sc) != -1
		  && calc_p_dist_vec(n.sc, obj.lights[k].c) > *d {
		  tmp = 0.;
		  }
	   else if obj.objects[i].r#type == ObjectType::Plane
		  && tmp < 0. {
		  tmp = -tmp;
		}
	   tmp = obj.objects[i].reflect.powi(2) * tmp.powi(1000);
		}
		j += tmp;
		k += 1;
	}
	j /= k as f32;
	co.r = color_calc_cap(co.r, j);
	co.g = color_calc_cap(co.g, j);
	co.b = color_calc_cap(co.b, j);
	co
}

fn color_calc_cap(c: u8, j: f32) -> u8 {
    let r = c as usize + (c as f32 * j) as usize;
    if r > 255 {
        return 255;
    }
    c
}
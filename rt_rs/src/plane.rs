

use libc::{c_float, c_int};
use sdl2::sys::SDL_Color;

use crate::{object::{ObjectItem, ObjectType, World}, vec4_calc::{Vector4, convert_str_to_vec4_with_w, calc_dp, calc_unit_v, calc_vect_to_point, calc_multi, calc_addition, calc_p_to_vec}, data_extraction::{get_reflect_refract, get_obj_options}, colour::{convert_str_to_color, blinn_phong}, ray::Ray, world::cnt_space, light::light_color, cartoon::cartoon_color};


pub fn plane_extraction(str: &str) -> ObjectItem {
	let mut obj = ObjectItem::default();
  obj.r#type = ObjectType::Plane;
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4_with_w(s.get(2).unwrap(), &mut obj.dir);
  get_reflect_refract(s.get(3).unwrap(), &mut obj);
  get_obj_options(s.get(4).unwrap(), &mut obj);
	convert_str_to_color(s.get(5).unwrap().to_string(), &mut obj.col);
  obj.h = 0.;
  obj.rad = 0.;
  obj.c = Vector4::default();
	obj
}

pub fn int_plane(obj: ObjectItem, d: &mut c_float, ray: Ray) {
  let mut di = obj.dir;
	di.w = 0.;
	let p = Vector4{
    x: obj.dir.x * obj.dir.w,
    y: obj.dir.y * obj.dir.w,
		z: obj.dir.z * obj.dir.w,
    w: 0.};
	di.w = calc_dp(p, di);
	let uv = calc_unit_v(ray.v);

	if calc_dp(ray.v, di) != 0.
	{
		let mut t = -(di.x * ray.sc.x + di.y * ray.sc.y + di.z *
				ray.sc.z + di.w);
		t /= di.x * uv.x + di.y * uv.y + di.z * uv.z;
		if t > 0. {
			*d = t;
    }
	}
}

pub fn check_plane(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut lines: usize = 1;
	while lines < 5 && (str.get(*i + lines).unwrap().chars().next().unwrap().is_numeric()
  || str.get(*i + lines).unwrap().starts_with('-'))
			 {
        lines += 1;
      }
	if lines != 5
	{
		eprintln!("Error: missing one or more elements in Plane");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Plane Error in name");
  }
	if cnt_space(str[*i], i, chk, 3) != 1 {
		eprintln!("Plane Error in coordinates");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Plane Error in reflection and refraction");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Plane Error in color");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Plane Error in color options");
  }
}

pub fn plane_refraction(obj: ObjectItem, ray: Ray, mut d: f32) -> Ray
{
	let mut rf = Ray::default();


		rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 0.995);
		let mut n = Vector4{
			x: obj.dir.x,
			y: obj.dir.y,
			z: obj.dir.z,
			w: 0.
		};
		if calc_dp(n, ray.v) < 0. {
			n = Vector4{x: -obj.dir.x, y: -obj.dir.y, z: -obj.dir.z, w: 0.};
		}
		n = calc_unit_v(n);
		let mut c1 = -calc_dp(calc_unit_v(ray.v), n);
		let mut nr = 1.000293 / obj.refract as f32;
		let mut c2 = 1. - nr * nr * (1. - c1 * c1);
		c2 = c2.sqrt();
		rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), nr),
				calc_multi(n, nr * c1 - c2)));
		int_plane(obj, &mut d, rf);
		rf.sc = calc_vect_to_point(rf.sc, rf.v, d * 1.005);
		n = calc_unit_v(Vector4{x: -obj.dir.x, y: -obj.dir.y, z: -obj.dir.z, w: 0.});
		c1 = -calc_dp(calc_unit_v(rf.v), n);
		nr = obj.refract as f32 / 1.000293;
		c2 = 1. - nr * nr * (1. - c1 * c1);
		c2 = c2.sqrt();
		rf.v = calc_addition(calc_multi(rf.v, nr), calc_multi(n, nr * c1 - c2));
	rf
}

pub fn plane_reflection(obj: ObjectItem, ray: Ray, d: c_float) -> Ray
{
	let mut rf = Ray::default();

    rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 0.995);
		let mut n = Vector4{
			x: obj.dir.x,
			y: obj.dir.y,
			z: obj.dir.z, 
			w: 0.};
		if calc_dp(n, ray.v) < 0. {
			n = Vector4{
				x: -obj.dir.x,
				y: -obj.dir.y,
				z: -obj.dir.z, 
				w: 0.};
		}
		let c1 = -calc_dp(n, calc_unit_v(ray.v));
		rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, 2. * c1));
	rf
}

pub fn color_plane(obj: &mut World, i: usize, rv: Ray, d: &mut f32) -> SDL_Color
{
	let plane = obj.objects[i];
	let mut n = Vector4{x: plane.dir.x, y: plane.dir.y, z: plane.dir.z, w: 0. };
	let p = calc_vect_to_point(rv.sc, rv.v, *d * 0.995);
	let l = calc_unit_v(calc_p_to_vec(p, obj.lights[0].c));
	// obj.objects[i] = texture(obj.objects[i], rv, n);
	if calc_dp(l, p) < 0. {
		n = Vector4{x: -plane.dir.x, y: -plane.dir.y, z: -plane.dir.z, w: 0. };
	}
	if obj.objects[i].reflect > 0. {
		return blinn_phong(obj, Ray{ sc:p, v: n}, i, rv.v, d);
	}
	light_color(obj, Ray{ sc:p, v: n}, i, d)
}

pub fn cartoon_plane(obj: & mut World, i: usize, rv: Ray, d: &mut f32) -> SDL_Color
{
	let plane = obj.objects[i];
	let n = Vector4{x: plane.dir.x, y: plane.dir.y, z: plane.dir.z, w: 0. };
	let p = calc_vect_to_point(rv.sc, rv.v, *d * 0.995);
	cartoon_color(obj, Ray{sc: p, v: n}, i, d)
}
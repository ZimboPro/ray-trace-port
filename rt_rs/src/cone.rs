use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{convert_str_to_vec4, calc_dp, calc_unit_v, calc_p_to_v, calc_vect_to_point, calc_p_dist, Vector4, calc_addition, calc_multi}, data_extraction::{get_reflect_refract, get_obj_options, get_rad_h}, colour::convert_str_to_color, ray::{Quad, Ray}, world::cnt_space};

pub fn cone_extraction(str: &str) -> ObjectItem {
  let mut obj = ObjectItem::default();
  obj.r#type = ObjectType::Cone;
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4(s.get(2).unwrap(), &mut obj.c);
  convert_str_to_vec4(s.get(3).unwrap(), &mut obj.dir);
  get_rad_h(s.get(4).unwrap(), &mut obj);
  get_reflect_refract(s.get(5).unwrap(), &mut obj);
	convert_str_to_color(s.get(6).unwrap().to_string(), &mut obj.col);
  get_obj_options(s.get(7).unwrap(), &mut obj);
  obj
}

pub fn int_cone(obj: ObjectItem, d: &mut c_float, ray: Ray) {
	let	mut cone = Quad::default();
	let ang = (((obj.rad / obj.h).atan()).cos()).powf(2.);
	let dv = calc_dp(calc_unit_v(ray.v), calc_unit_v(obj.dir));
	let co = calc_p_to_v(obj.c, ray.sc);
	let cov = calc_dp(calc_unit_v(obj.dir), co);
	cone.a = dv * dv - ang;
	cone.b = 2. * (dv * cov - calc_dp(calc_unit_v(ray.v), co) * ang);
	cone.c = cov * cov - calc_dp(co, co) * ang;
	cone.c = (cone.b * cone.b) - (4. * cone.a * cone.c);
	if cone.c >= 0. {
    cone.t1 = (-cone.b + cone.c.sqrt()) / (2. * cone.a);
    cone.t2 = (-cone.b - cone.c.sqrt()) / (2. * cone.a);
    if cone.t1 >= 0. {
      *d = cone.t1;
    }
    if cone.t2 >= 0. && (cone.t2 < cone.t1 || *d == -1.) {
      *d = cone.t2;
    }
    if *d != -1.
    {
      let cp = calc_p_to_v(obj.c, calc_vect_to_point(ray.sc, ray.v, *d));
      if calc_dp(cp, obj.dir) < 0. {
        *d = -1.;
      }
    }
  }
}

pub fn cone_norm(obj: ObjectItem, d: c_float, ray: Ray) -> Vector4 {
	let p = calc_vect_to_point(ray.sc, ray.v, d);
	let di = calc_p_dist(p, obj.c).powf(2.) / calc_dp(calc_p_to_v(obj.c, p),
			calc_unit_v(obj.dir));
	calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di), p))
}

pub fn check_cone(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut lines: usize = 1;
	while lines < 7 && (str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric()
  || str.get(*i + lines).unwrap().chars().nth(0).unwrap() == '-')
			 {
        lines += 1;
      }
	if lines != 7
	{
		eprintln!("Error: missing one or more elements in Cone");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Cone Error in name");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cone Error in coordinates");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cone Error in direction");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Cone Error in radius and hieght");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Cone Error in reflection and refraction");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cone Error in color");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cone Error in color options");
  }
}

pub fn cone_refraction(obj: ObjectItem, ray: Ray, mut d: c_float) -> Ray
{
	let mut rf = Ray::default();

  unsafe {
    rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 1.05);
    let mut n = calc_unit_v(cone_norm(obj, d * 1.05, ray));
    let mut c1 = -calc_dp(calc_unit_v(ray.v), n);
    let mut di = 1.000293 / (obj.refract as f32 / 1000000.);
    let mut c2 = 1. - di * di * (1. - c1 * c1);
    c2 = c2.sqrt();
    rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), di),
        calc_multi(n, di * c1 - c2)));
    let mut d = -1.;
    int_cone(obj, &mut d, rf);
    if d == -1. {
      return Ray {
        sc: rf.sc,
        v: ray.v
      };
    }
    n = calc_unit_v(cone_norm(obj, d * 1.005, rf));
    c1 = calc_dp(calc_unit_v(rf.v), n);
    di = (obj.refract as f32 / 1000000.) / 1.000293;
    c2 = 1. - di * di * (1. - c1 * c1);
    c2 = c2.sqrt();
    rf.v = calc_unit_v(calc_addition(calc_multi(rf.v, di), calc_multi(n,
          di * c1 - c2)));
    d = -1.;
    int_cone(obj, &mut d, rf);
    if d != -1. {
      return Ray {
        sc: rf.sc,
        v: ray.v
      };
    }
  }
	rf
}

pub fn cone_reflection(obj: ObjectItem, ray: Ray, d: c_float) -> Ray
{
	let mut rf = Ray::default();

  unsafe {
    rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 0.995);
    let di = calc_p_dist(rf.sc, obj.c).powf(2.) / calc_dp(calc_p_to_v(obj.c,
          rf.sc), calc_unit_v(obj.dir));
    let n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di),
          rf.sc));
    let c1 = -calc_dp(n, calc_unit_v(ray.v));
    rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, 2. * c1));
  }
	rf
}
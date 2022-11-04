use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, data_extraction::{get_rad_h, get_reflect_refract, get_obj_options}, vec4_calc::{convert_str_to_vec4, calc_dp, calc_unit_v, calc_p_to_v, Vector4, calc_vect_to_point, calc_addition, calc_multi}, colour::convert_str_to_color, ray::{Quad, Ray}, world::cnt_space};

#[no_mangle]
pub unsafe extern "C" fn cylinder(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          cylinder_extraction( s.to_string(), obj);
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn cylinder_extraction(str: String, obj: &mut ObjectItem) {
  obj.r#type = ObjectType::Cylinder;
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4(s.get(2).unwrap(), &mut obj.c);
  convert_str_to_vec4(s.get(3).unwrap(), &mut obj.dir);
  get_rad_h(s.get(4).unwrap(), obj);
  get_reflect_refract(s.get(5).unwrap(), obj);
	convert_str_to_color(s.get(6).unwrap().to_string(), &mut obj.col);
  get_obj_options(s.get(7).unwrap(), obj);
}

#[no_mangle]
pub unsafe extern "C" fn int_cyl(obj: ObjectItem, d: &mut c_float, ray: Ray) {
  let mut cyl = Quad::default();
	let dv = calc_dp(calc_unit_v(obj.dir), calc_unit_v(ray.v));
	let co = calc_p_to_v(obj.c, ray.sc);
	let cov = calc_dp(co, calc_unit_v(obj.dir));
	cyl.a = 1. - dv * dv;
	cyl.b = 2. * calc_dp(co, calc_unit_v(ray.v)) - 2. * dv * cov;
	cyl.c = calc_dp(co, co) - cov * cov - obj.rad * obj.rad;
	cyl.c = (cyl.b * cyl.b) - (4. * cyl.a * cyl.c);
	if cyl.c > 0. {
    cyl.t1 = (-cyl.b + cyl.c.sqrt()) / (2. * cyl.a);
    cyl.t2 = (-cyl.b - cyl.c.sqrt()) / (2. * cyl.a);
    if cyl.t1 >= 0. {
      *d = cyl.t1;
    }
    if cyl.t2 >= 0. && (cyl.t2 < cyl.t1 || *d == -1.) {
      *d = cyl.t2;
    }
  }
}

#[no_mangle]
pub unsafe extern "C" fn cyl_norm(obj: ObjectItem, d: c_float, ray: Ray) -> Vector4 {
	let p = calc_vect_to_point(ray.sc, ray.v, d);
	let di = calc_dp(calc_p_to_v(obj.c, p), calc_unit_v(obj.dir));
	calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di), p))
}

pub fn check_cylinder(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut lines: usize = 1;
	while lines < 7 && (str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric()
  || str.get(*i + lines).unwrap().chars().nth(0).unwrap() == '-')
			{
        lines += 1;
      }
	if lines != 7
	{
		eprintln!("Error: missing one or more elements in Cylinder");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Cylinder Error in name");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cylinder Error in coordinates");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cylinder Error in direction");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Cylinder Error in radius and hieght");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Cylinder Error in reflection and refraction");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cylinder Error in color");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Cylinder Error in color options");
  }
}

pub fn cylinder_refraction(obj: ObjectItem, ray: Ray, mut d: f32) -> Ray
{
	let mut rf = Ray::default();

  unsafe {

    rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 1.00005);
    let mut n = calc_unit_v(cyl_norm(obj, d * 1.005, ray));
    let mut c1 = -calc_dp(calc_unit_v(ray.v), n);
    let mut di = 1.000293 / (obj.refract as f32 / 1000000.);
    let mut c2 = 1. - di * di * (1. - c1 * c1);
    c2 = c2.sqrt();
    rf.v = calc_unit_v(calc_addition(calc_multi(calc_unit_v(ray.v), di),
        calc_multi(n, di * c1 - c2)));
    d = -1.;
    int_cyl(obj, &mut d, rf);
    if d == -1. {
      return Ray {
        sc: rf.sc,
        v: ray.v
      };
    }
    rf.sc = calc_vect_to_point(rf.sc, rf.v, d * 1.005);
    n = calc_unit_v(cyl_norm(obj, d * 1.005, rf));
    c1 = calc_dp(calc_unit_v(rf.v), n);
    di = (obj.refract as f32 / 1000000.) / 1.000293;
    c2 = 1. - di * di * (1. - c1 * c1);
    c2 = c2.sqrt();
    rf.v = calc_unit_v(calc_addition(calc_multi(rf.v, di), calc_multi(n,
            di * c1 - c2)));
  }
	rf
}

pub fn cylinder_reflection(obj: ObjectItem, ray: Ray, d: c_float) -> Ray
{
	let mut rf = Ray::default();

  unsafe {
    rf.sc = calc_vect_to_point(ray.sc, ray.v, d * 0.995);
    let di = calc_dp(calc_p_to_v(obj.c, rf.sc), calc_unit_v(obj.dir));
    let n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di),
          rf.sc));
    let c1 = -calc_dp(n, calc_unit_v(ray.v));
    rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, 2. * c1));
  }
	rf
}
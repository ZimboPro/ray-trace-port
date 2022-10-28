use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{convert_str_to_vec4, calc_dp, calc_unit_v, calc_p_to_v, calc_vect_to_point, calc_p_dist, Vector4}, data_extraction::{get_reflect_refract, get_obj_options, get_rad_h}, colour::convert_str_to_color, ray::{Quad, Ray}, world::cnt_space};


#[no_mangle]
pub unsafe extern "C" fn cone(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          cone_extraction( s.to_string(), obj);
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn cone_extraction(str: String, obj: &mut ObjectItem) {
  obj.r#type = ObjectType::Cone;
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4(s.get(2).unwrap(), &mut obj.c);
  convert_str_to_vec4(s.get(3).unwrap(), &mut obj.dir);
  get_rad_h(s.get(4).unwrap(), obj);
  get_reflect_refract(s.get(5).unwrap(), obj);
	convert_str_to_color(s.get(6).unwrap().to_string(), &mut obj.col);
  get_obj_options(s.get(7).unwrap(), obj);
}

#[no_mangle]
pub unsafe extern "C" fn int_cone(obj: ObjectItem, d: &mut c_float, ray: Ray) {
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

#[no_mangle]
pub unsafe extern "C" fn cone_norm(obj: ObjectItem, d: c_float, ray: Ray) -> Vector4 {
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
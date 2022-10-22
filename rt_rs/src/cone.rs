use std::ffi::CStr;

use libc::{c_char, c_float};

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{convert_str_to_vec4, calc_dp, calc_unit_v, calc_p_to_v, calc_vect_to_point}, data_extraction::{get_reflect_refract, get_obj_options, get_rad_h}, colour::convert_str_to_color, ray::{Quad, Ray}};


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
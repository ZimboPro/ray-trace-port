use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, data_extraction::{get_rad_h, get_reflect_refract, get_obj_options}, vec4_calc::{convert_str_to_vec4, calc_dp, calc_unit_v, calc_p_to_v, Vector4, calc_vect_to_point}, colour::convert_str_to_color, ray::{Quad, Ray}, world::cnt_space};

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
        println!("Line {}", lines);
        println!("T Line {}", *i + lines);
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
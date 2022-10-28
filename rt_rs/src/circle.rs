use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{Vector4, convert_str_to_vec4, calc_p_to_v, calc_dp, calc_unit_v}, colour::{convert_str_to_color}, data_extraction::{get_reflect_refract, get_obj_options, get_rad_h}, ray::{Ray, Quad}, world::cnt_space};

#[no_mangle]
pub unsafe extern "C" fn ft_circle(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          circle_extraction( s.to_string(), obj);
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn circle_extraction(str: String, obj: &mut ObjectItem)
{
  obj.r#type = ObjectType::Circle;
  obj.h = 0.;
  obj.dir = Vector4::default();
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4(s.get(2).unwrap(), &mut obj.c);
  get_rad_h(s.get(3).unwrap(), obj);
  get_reflect_refract(s.get(4).unwrap(), obj);
	convert_str_to_color(s.get(5).unwrap().to_string(), &mut obj.col);
  get_obj_options(s.get(6).unwrap(), obj);
  // TODO map to correct values
	// obj.texmap = props.get(3).unwrap().as_bytes().as_ptr();
}

#[no_mangle]
pub unsafe extern "C" fn int_circle(circ: ObjectItem, d: &mut c_float, ray: Ray) {
  let mut ci = Quad::default();
  
  let co = calc_p_to_v(circ.c, ray.sc);
	ci.a = 1.;
	ci.b = 2. * calc_dp(calc_unit_v(ray.v), co);
	ci.c = calc_dp(co, co) - (circ.rad * circ.rad);
	ci.c = (ci.b * ci.b) - (4. * ci.a * ci.c);
	if ci.c >= 0. {
		ci.t1 = (-ci.b + ci.c.sqrt()) / (2. * ci.a);
    ci.t2 = (-ci.b - ci.c.sqrt()) / (2. * ci.a);
    if ci.t1 > 0. && ci.t2 > 0.
    {
      if ci.t1 <= ci.t2 {
        *d = ci.t1;
      } else {
        *d = ci.t2;
      }
    }
    else if ci.t1 > 0. {
      *d = ci.t1;
    } else if ci.t2 > 0. {
      *d = ci.t2;
    }
  }
}

pub fn check_circle(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{

	let mut lines: usize = 1;
	while lines < 6 && (str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric()
  || str.get(*i + lines).unwrap().chars().nth(0).unwrap() == '-')
			 {
        lines += 1;
      }
	if lines != 6
	{
		eprintln!("Error: missing one or more elements in Circle");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Circle Error in name");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Circle Error in coordinates");
  }
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Circle Error in radius");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Circle Error in reflection and refraction");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Circle Error in color");
  }
	if cnt_space(str[*i], i, chk, 3) != 1 {
		eprintln!("Circle Error in color options");
  }
}
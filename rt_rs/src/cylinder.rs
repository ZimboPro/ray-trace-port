use std::ffi::CStr;

use libc::c_char;

use crate::{object::{ObjectItem, ObjectType}, data_extraction::{get_rad_h, get_reflect_refract, get_obj_options}, vec4_calc::convert_str_to_vec4, colour::convert_str_to_color};

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

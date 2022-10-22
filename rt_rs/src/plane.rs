use std::ffi::CStr;

use libc::c_char;

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{Vector4, convert_str_to_vec4_with_w}, data_extraction::{get_reflect_refract, get_obj_options}, colour::convert_str_to_color};


#[no_mangle]
pub unsafe extern "C" fn plane(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          plane_extraction( s.to_string(), obj);
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn plane_extraction(str: String, obj: &mut ObjectItem) {
  obj.r#type = ObjectType::Plane;
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4_with_w(s.get(2).unwrap(), &mut obj.dir);
  get_reflect_refract(s.get(3).unwrap(), obj);
  get_obj_options(s.get(4).unwrap(), obj);
	convert_str_to_color(s.get(5).unwrap().to_string(), &mut obj.col);
  obj.h = 0.;
  obj.rad = 0.;
  obj.c = Vector4::default();
}
use std::ffi::CStr;

use libc::c_char;

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::convert_str_to_vec4, data_extraction::{get_reflect_refract, get_obj_options}, colour::convert_str_to_color};


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
  let props: Vec<&str> = s.get(4).unwrap().split(' ').collect();
	obj.rad = props.get(0).unwrap().parse::<f32>().unwrap();
	obj.h = props.get(1).unwrap().parse::<f32>().unwrap();
  get_reflect_refract(s.get(5).unwrap(), obj);
	convert_str_to_color(s.get(6).unwrap().to_string(), &mut obj.col);
  get_obj_options(s.get(7).unwrap(), obj);
}
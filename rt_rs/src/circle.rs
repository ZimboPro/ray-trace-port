use std::ffi::CStr;

use libc::c_char;

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{Vector4, convert_str_to_vec4}, colour::{convert_str_to_color}, data_extraction::{get_reflect_refract, get_obj_options, get_rad_h}};

#[no_mangle]
pub unsafe extern "C" fn ft_circle(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          ft_circ( s.to_string(), obj);
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn ft_circ(str: String, obj: &mut ObjectItem)
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

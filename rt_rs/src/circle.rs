use std::ffi::CStr;

use libc::c_char;

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{Vector4, str_map_to_vec4_def, convert_str_to_vec4}, colour::{str_map_to_color, convert_str_to_color}};

#[no_mangle]
pub unsafe extern "C" fn ft_circle(obj: &mut ObjectItem, str: *const c_char) {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          obj.r#type = ObjectType::Circle;
          ft_circ( s.to_string(), obj);
          obj.h = 0.;
          obj.dir = Vector4::default();
        },
        Err(_) => eprintln!("String Error for Circle")
      }
    }
}

fn ft_circ(str: String, obj: &mut ObjectItem)
{
	let s: Vec<&str> = str.split('\n').collect();
  convert_str_to_vec4(s.get(2).unwrap(), &mut obj.c);
	obj.rad = s.get(3).unwrap().parse::<f32>().unwrap();
	let mut props: Vec<&str> = s.get(4).unwrap().split(' ').collect();
	obj.reflect = props.get(0).unwrap().parse::<f32>().unwrap() / 100.;
	obj.refract = props.get(1).unwrap().parse::<i32>().unwrap();
	convert_str_to_color(s.get(5).unwrap().to_string(), &mut obj.col);
	props = s.get(6).unwrap().split(' ').collect();
	// if (ft_atoi(s[0]))
	// 	obj.c = ft_rand(obj.c);
	obj.pattern = props.get(1).unwrap().parse::<i32>().unwrap();
	obj.filter = props.get(2).unwrap().parse::<i32>().unwrap();
  // TODO map to correct values
	// obj.texmap = props.get(3).unwrap().as_bytes().as_ptr();
}

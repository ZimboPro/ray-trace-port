use std::ffi::CStr;

use libc::{c_char, c_float, c_int};

use crate::{object::{ObjectItem, ObjectType}, vec4_calc::{Vector4, convert_str_to_vec4_with_w, calc_dp, calc_unit_v}, data_extraction::{get_reflect_refract, get_obj_options}, colour::convert_str_to_color, ray::Ray, world::cnt_space};


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

#[no_mangle]
pub unsafe extern "C" fn int_plane(obj: ObjectItem, d: &mut c_float, ray: Ray) {
  let mut di = obj.dir;
	di.w = 0.;
	let p = Vector4{
    x: obj.dir.x * obj.dir.w,
    y: obj.dir.y * obj.dir.w,
		z: obj.dir.z * obj.dir.w,
    w: 0.};
	di.w = calc_dp(p, di);
	let uv = calc_unit_v(ray.v);

	if calc_dp(ray.v, di) != 0.
	{
		let mut t = -(di.x * ray.sc.x + di.y * ray.sc.y + di.z *
				ray.sc.z + di.w);
		t /= di.x * uv.x + di.y * uv.y + di.z * uv.z;
		if t > 0. {
			*d = t;
    }
	}
}

pub fn check_plane(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut lines: usize = 1;
	while lines < 5 && (str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric()
  || str.get(*i + lines).unwrap().chars().nth(0).unwrap() == '-')
			 {
        lines += 1;
      }
	if lines != 5
	{
		eprintln!("Error: missing one or more elements in Plane");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {
		eprintln!("Plane Error in name");
  }
	if cnt_space(str[*i], i, chk, 3) != 1 {
		eprintln!("Plane Error in coordinates");
  }
	if cnt_space(str[*i], i, chk, 1) != 1 {
		eprintln!("Plane Error in reflection and refraction");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Plane Error in color");
  }
	if cnt_space(str[*i], i, chk, 2) != 1 {
		eprintln!("Plane Error in color options");
  }
}
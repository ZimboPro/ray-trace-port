use std::ffi::CStr;

use glam::Vec4;
use libc::c_char;

#[no_mangle]
pub unsafe extern "C" fn calc_addition(a: Vec4, b: Vec4) -> Vec4 {
  let mut ans = a + b;
  ans.w = 0.;
  ans
}

#[no_mangle]
pub unsafe extern "C" fn str_to_vec4(val: *const c_char) -> Vec4 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                let mut v = Vec4::default();
                
                    v.x = points.get(0).unwrap().parse::<f32>().unwrap();
                    v.y = points.get(1).unwrap().parse::<f32>().unwrap();
                    v.z = points.get(2).unwrap().parse::<f32>().unwrap();
                    v.w = points.get(3).unwrap().parse::<f32>().unwrap();
                    v
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                Vec4::default()
},
        };
    }
    eprintln!("String is null");
    Vec4::default()

}


#[no_mangle]
pub unsafe extern "C" fn str_map_to_vec4(val: *const c_char, vec: &mut Vec4) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                    vec.x = points.get(0).unwrap().parse::<f32>().unwrap();
                    vec.y = points.get(1).unwrap().parse::<f32>().unwrap();
                    vec.z = points.get(2).unwrap().parse::<f32>().unwrap();
                    vec.w = points.get(3).unwrap().parse::<f32>().unwrap();
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                vec.x = 0.;
                vec.y = 0.;
                vec.z = 0.;
                vec.w = 0.;
            },
        };
    }
    eprintln!("String is null");
    vec.x = 0.;
    vec.y = 0.;
    vec.z = 0.;
    vec.w = 0.;
}
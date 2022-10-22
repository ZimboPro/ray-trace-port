use std::ffi::CStr;

use glam::Vec3;
use libc::{c_char, c_float};


#[no_mangle]
pub unsafe extern "C" fn str_to_vec3(val: *const c_char) -> Vec3 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                Vec3 {
                    x: points.first().unwrap().parse::<f32>().unwrap(),
                    y: points.get(1).unwrap().parse::<f32>().unwrap(),
                    z: points.get(2).unwrap().parse::<f32>().unwrap(),
                }
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                Vec3 { x: 0., y: 0., z: 0. }
            },
        };
    }
    eprintln!("String is null");
    Vec3 { x: 0., y: 0., z: 0. }
}


#[no_mangle]
pub unsafe extern "C" fn str_map_to_vec3(val: *const c_char, vec: &mut Vec3) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                    vec.x = points.first().unwrap().parse::<f32>().unwrap();
                    vec.y = points.get(1).unwrap().parse::<f32>().unwrap();
                    vec.z = points.get(2).unwrap().parse::<f32>().unwrap();
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                vec.x = 0.;
                vec.y = 0.;
                vec.z = 0.;
            },
        };
    }
    eprintln!("String is null");
    vec.x = 0.;
    vec.y = 0.;
    vec.z = 0.;
}

#[no_mangle]
pub unsafe extern "C" fn calc_multi_vec(a: Vec3, d: c_float) -> Vec3 {
 a * d
}
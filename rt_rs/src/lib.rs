use atoi::atoi;
use glam::{Vec3, Vec4};
use libc::{c_char, c_int};
use std::ffi::CStr;
mod colour;
mod object;

#[no_mangle]
pub unsafe extern "C" fn ft_atoi_rs(val: *const c_char) -> c_int {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);

        return match raw.to_str() {
            Ok(s) => {
                return match atoi::<c_int>(s.as_bytes()) {
                    Some(v) => v,
                    None => 0,
                };
            }
            Err(_) => 0,
        };
    }
    0
}

#[no_mangle]
pub unsafe extern "C" fn str_to_vec3(val: *const c_char) -> Vec3 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                Vec3 {
                    x: points.get(0).unwrap().parse::<f32>().unwrap(),
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
                    vec.x = points.get(0).unwrap().parse::<f32>().unwrap();
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

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}

use std::ffi::CStr;

use glam::{Vec4, Vec3};
use libc::{c_char, c_float};

#[repr(C)]
#[derive(Default)]
pub struct Vector4 {
  x: c_float,
  y: c_float,
  z: c_float,
  w: c_float,
}

impl From<Vec4> for Vector4 {
    fn from(vec: Vec4) -> Self {
        Self { x: vec.x, y: vec.y, z: vec.z, w: vec.w }
    }
}

impl From<Vector4> for Vec4 {
  fn from(vec: Vector4) -> Self {
    let mut a = Self::default();
    a.x = vec.x;
    a.y = vec.y;
    a.z = vec.z;
    a.w = vec.w;
    a
  }
}

impl From<Vec3> for Vector4 {
    fn from(vec: Vec3) -> Self {
        Self { x: vec.x, y: vec.y, z: vec.z, w: 0. }
    }
}

impl From<Vector4> for Vec3 {
  fn from(vec: Vector4) -> Self {
    let mut a = Self::default();
    a.x = vec.x;
    a.y = vec.y;
    a.z = vec.z;
    a
  }
}

#[no_mangle]
pub unsafe extern "C" fn calc_addition(a: Vector4, b: Vector4) -> Vector4 {
  let a: Vec4 = a.into(); 
  let b: Vec4 = b.into(); 
  let mut ans: Vec4 = a + b;
  ans.w = 0.;
  ans.into()
}

#[no_mangle]
pub unsafe extern "C" fn calc_cross_product(a: Vector4, b: Vector4) -> Vector4 {
  let a: Vec3 = a.into(); 
  let b: Vec3 = b.into(); 
  let mut ans = a.cross(b);
  ans.into()
}

#[no_mangle]
pub unsafe extern "C" fn calc_m(a: Vector4) -> c_float {
  let a: Vec3 = a.into(); 
  a.length()
}

#[no_mangle]
pub unsafe extern "C" fn calc_dp(a: Vector4, b: Vector4) -> c_float {
  let a: Vec3 = a.into(); 
  let b: Vec3 = b.into();
  a.dot(b)
}

#[no_mangle]
pub unsafe extern "C" fn calc_multi(a: Vector4, d: c_float) -> Vector4 {
  let mut a: Vec4 = a.into(); 
  let f = a.w;
  a = a * d;
  a.w = f;
  a.into()
}

#[no_mangle]
pub unsafe extern "C" fn str_to_vec4(val: *const c_char) -> Vector4 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                let mut v = Vector4::default();
                
                    v.x = points.get(0).unwrap().parse::<c_float>().unwrap();
                    v.y = points.get(1).unwrap().parse::<c_float>().unwrap();
                    v.z = points.get(2).unwrap().parse::<c_float>().unwrap();
                    v.w = points.get(3).unwrap().parse::<c_float>().unwrap();
                    v
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                Vector4::default()
},
        };
    }
    eprintln!("String is null");
    Vector4::default()
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
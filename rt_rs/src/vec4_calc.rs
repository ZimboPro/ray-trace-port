use std::ffi::CStr;

use glam::{Vec4, Vec3};
use libc::{c_char, c_float};

#[repr(C)]
#[derive(Default, Clone, Copy)]
pub struct Vector4 {
  pub x: c_float,
  pub y: c_float,
  pub z: c_float,
  pub w: c_float,
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


pub fn calc_addition(a: Vector4, b: Vector4) -> Vector4 {
  let a: Vec4 = a.into(); 
  let b: Vec4 = b.into(); 
  let mut ans: Vec4 = a + b;
  ans.w = 0.;
  ans.into()
}


pub fn calc_cross_product(a: Vector4, b: Vector4) -> Vector4 {
  let a: Vec3 = a.into(); 
  let b: Vec3 = b.into(); 
  a.cross(b).into()
}


pub fn calc_m(a: Vector4) -> c_float {
  let a: Vec3 = a.into(); 
  a.length()
}


pub fn calc_unit_v(a: Vector4) -> Vector4 {
  let a: Vec4 = a.into(); 
  a.normalize().into()
}


pub fn calc_dp(a: Vector4, b: Vector4) -> c_float {
  let a: Vec3 = a.into(); 
  let b: Vec3 = b.into();
  a.dot(b)
}


pub fn calc_multi(a: Vector4, d: c_float) -> Vector4 {
  let mut a: Vec4 = a.into(); 
  let f = a.w;
  a *= d;
  a.w = f;
  a.into()
}


pub fn calc_p_to_v(a: Vector4, b: Vector4) -> Vector4 {
  let a: Vec4 = a.into(); 
  let b: Vec4 = b.into(); 
  let mut ans = b - a;
  ans.w = 0.;
  ans.into()
}


pub fn calc_p_dist(a: Vector4, b: Vector4) -> c_float {
  let a: Vec4 = a.into(); 
  let b: Vec4 = b.into(); 
  (b - a).length()
}


pub fn calc_p_dist_vec(a: Vector4, b: Vec3) -> c_float {
  let a: Vec3 = a.into(); 
  (b - a).length()
}


pub fn calc_p_to_vec(a: Vector4, b: Vec3) -> Vector4 {
  let a: Vec3 = a.into(); 
  (b - a).into()
}


pub fn calc_vector_ang(a: Vector4, b: Vector4) -> c_float {
  let a: Vec3 = a.into(); 
  let b: Vec3 = b.into(); 
  a.angle_between(b)
}


pub fn calc_vect_to_point(p: Vector4, v: Vector4, m: c_float) -> Vector4 {
  let p : Vec4 = p.into();
  let v : Vec4 = v.into();
	let mut ans = p + v * (m / v.length());
	ans.w = 1.;
	ans.into()
}


pub fn calc_normal(v: Vector4, a: Vector4, b: Vector4)-> Vector4 {
  let ab: Vec4 = calc_p_to_v(a, b).into();
	let t = ab.length();
	let ang = calc_vector_ang(v, ab.into());
	let t = t * ang.cos();
	let p = calc_vect_to_point(a, v, t);
	calc_p_to_v(p, b)
}


pub fn	rot_x(v:  Vector4, r: c_float) -> Vector4
{
  let mut ans = v;
	let y = ans.y;
	let z = ans.z;
	ans.y = y * r.cos() - z * r.sin();
	ans.z = y * r.sin() + z * r.cos();
	ans
}


pub fn	rot_y(v:  Vector4, r: c_float) -> Vector4
{
  let mut ans = v;
	let x = ans.x;
	let z = ans.z;
	ans.x = x * r.cos() + z * r.sin();
	ans.z = -x * r.sin() + z * r.cos();
	ans
}

#[no_mangle]
pub unsafe extern "C" fn str_to_vec4(val: *const c_char) -> Vector4 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                let mut v = Vector4::default();
                
                    v.x = points.first().unwrap().parse::<c_float>().unwrap();
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
pub unsafe extern "C" fn str_to_vec4_def(val: *const c_char) -> Vector4 {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                let points: Vec<&str> = s.split(' ').collect();
                let mut v = Vector4::default();
                
                    v.x = points.first().unwrap().parse::<c_float>().unwrap();
                    v.y = points.get(1).unwrap().parse::<c_float>().unwrap();
                    v.z = points.get(2).unwrap().parse::<c_float>().unwrap();
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
pub unsafe extern "C" fn str_map_to_vec4(val: *const c_char, vec: &mut Vector4) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
              convert_str_to_vec4_with_w(s, vec);
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


pub fn convert_str_to_vec4_with_w(s: &str, vec: &mut Vector4) {
  let points: Vec<&str> = s.split(' ').collect();
  vec.x = points.first().unwrap().parse::<f32>().unwrap();
  vec.y = points.get(1).unwrap().parse::<f32>().unwrap();
  vec.z = points.get(2).unwrap().parse::<f32>().unwrap();
  vec.w = points.get(3).unwrap().parse::<f32>().unwrap();
}

#[no_mangle]
pub unsafe extern "C" fn str_map_to_vec4_def(val: *const c_char, vec: &mut Vector4) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                convert_str_to_vec4(s, vec);
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

pub fn convert_str_to_vec4(s: &str, vec: &mut Vector4) {
  let points: Vec<&str> = s.split(' ').collect();
  vec.x = points.first().unwrap().parse::<f32>().unwrap();
  vec.y = points.get(1).unwrap().parse::<f32>().unwrap();
  vec.z = points.get(2).unwrap().parse::<f32>().unwrap();
  vec.w = 0.;
}
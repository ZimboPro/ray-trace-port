use atoi::atoi;

use libc::{c_char, c_int};
use std::ffi::CStr;
mod colour;
mod object;
mod vec3_calc;
mod vec4_calc;
mod ray;
mod camera;
mod pixel;
mod circle;
mod data_extraction;
mod cone;
mod cylinder;
mod plane;
mod world;
mod light;
mod refraction;
mod reflection;
mod interaction;
mod fresnel;
mod perlin;

#[no_mangle]
pub unsafe extern "C" fn ft_atoi_rs(val: *const c_char) -> c_int {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);

        return match raw.to_str() {
            Ok(s) => {
                return atoi::<c_int>(s.as_bytes()).unwrap_or(0);
            }
            Err(_) => 0,
        };
    }
    0
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

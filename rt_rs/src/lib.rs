use libc::{c_char, c_int};
use std::ffi::CStr;
use std::ptr;
use atoi::atoi;

#[no_mangle]
pub unsafe extern "C" fn ft_atoi_rs(val: * const c_char)-> c_int {
  if !val.is_null() {
    let raw = CStr::from_ptr(val);

    return match raw.to_str() {
        Ok(s) => {
          return match atoi::<c_int>(s.as_bytes()) {
            Some(v) => v,
            None => 0,
        };
        },
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

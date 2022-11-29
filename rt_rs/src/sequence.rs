use std::{path::PathBuf, fs, ffi::{CStr, c_char}};

use crate::{object::objects, ray::raytrace, world::validate_file_contents};

#[no_mangle]
pub unsafe extern "C" fn sequence(val: *const c_char, is_aa: u8) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        match raw.to_str() {
          Ok(file_name) => {
            if validate_file_contents(file_name.into()) == 1 {
              let path: PathBuf = file_name.into();
              let contents = fs::read_to_string(path).unwrap();
              let mut obj = objects(&contents);
              raytrace(&mut obj, is_aa);
            }
          },
          Err(e) => eprintln!("File name error: {}", e)
        }
    }
}

#[no_mangle]
pub unsafe extern "C" fn sequence_aa(val: *const c_char) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        match raw.to_str() {
          Ok(file_name) => {
            if validate_file_contents(file_name.into()) == 1 {
              let path: PathBuf = file_name.into();
              let contents = fs::read_to_string(path).unwrap();
              let mut obj = objects(&contents);
              raytrace(&mut obj, 1);
            }
          },
          Err(e) => eprintln!("File name error: {}", e)
        }
    }
}
use std::{path::PathBuf, fs, ffi::{CStr, c_char}};

use crate::{world::{validate_file_contents}, object::objects, ray::raytrace};

#[no_mangle]
pub unsafe extern "C" fn sequence(val: *const c_char) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);

        match raw.to_str() {
          Ok(file_name) => {
            if validate_file_contents(file_name.into()) == 1 {
              let path: PathBuf = file_name.into();
              let contents = fs::read_to_string(path).unwrap();
              let mut obj = objects(&contents);
              raytrace(&mut obj);
            }
          },
          Err(e) => eprintln!("File name error: {}", e)
        }
    }
}
use std::{path::PathBuf, fs, ffi::{CStr}};

use libc::c_char;

use crate::{object::objects, ray::raytrace, world::validate_file_contents, non_aa_seq, aa_seq};

#[no_mangle]
pub unsafe extern "C" fn sequence(val: *const c_char) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        match raw.to_str() {
          Ok(file_name) => {
            non_aa_seq(file_name);
          },
          Err(e) => eprintln!("File name error: {}", e)
        }
    }
}

// pub fn non_aa_seq(file_name: &str) {
//   if validate_file_contents(file_name.into()) == 1 {
//     let path: PathBuf = file_name.into();
//     let contents = fs::read_to_string(path).unwrap();
//     let mut obj = objects(&contents);
//     raytrace(&mut obj, false);
//   }
// }

// pub fn aa_seq(file_name: &str) {
//   if validate_file_contents(file_name.into()) == 1 {
//     let path: PathBuf = file_name.into();
//     let contents = fs::read_to_string(path).unwrap();
//     let mut obj = objects(&contents);
//     raytrace(&mut obj, true);
//   }
// }

#[no_mangle]
pub unsafe extern "C" fn sequence_aa(val: *const c_char) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        match raw.to_str() {
          Ok(file_name) => {
            aa_seq(file_name);
          },
          Err(e) => eprintln!("File name error: {}", e)
        }
    }
}
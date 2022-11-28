use std::{path::PathBuf, fs};

use crate::world::{validate_file_contents};

pub unsafe extern "C" fn sequence(file_name: &str) {
  if validate_file_contents(file_name.into()) == 1 {
    let path: PathBuf = file_name.into();
    let contents = fs::read_to_string(path).unwrap();
  }
}
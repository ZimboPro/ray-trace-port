use std::{path::PathBuf, fs};

use libc::{c_int};

use crate::{circle::check_circle, cone::check_cone, plane::check_plane, cylinder::check_cylinder, camera::check_camera, light::check_light};

pub fn validate_file_contents(path: PathBuf) -> c_int {
  let contents = fs::read_to_string(path).unwrap();
  let mut chk: c_int = check_if_camera_light_and_obj(&contents);
  let lines: Vec<&str> = contents.split('\n').collect();
  let mut i = 0;
  while i < lines.len() {
      match lines[i] {
        "Circle" => {
          check_circle(&lines, &mut i,  &mut chk);
        },
        "Cone" => {
          check_cone(&lines, &mut i,  &mut chk);
        },
        "Plane" => {
          check_plane(&lines, &mut i,  &mut chk);
        },
        "Cylinder" => {
          check_cylinder(&lines, &mut i,  &mut chk);
        },
        "Camera" => {
          check_camera(&lines, &mut i, &mut chk);
        },
        "Lights" => {
          check_light(&lines, &mut i, &mut chk);
        },
        _ => {}
      }
      i += 1;
  }
  if chk != 1 {
    return 0;
  }
  1
}

pub fn cnt_space(str: &str, j: &mut usize, chk :&mut c_int, value: usize) -> c_int {
  *j += 1;
  if str.matches(' ').count() != value {
    *chk = 0;
    return 0;
  }
  1
}

fn check_if_camera_light_and_obj(contents: &str) -> c_int {
  let mut chk = match contents.matches("Camera").count() {
    0 => {
      eprintln!("No camera");
      0
    }
    1 => 1,
    _ => {
      eprintln!("Too many cameras");
      0
    }
  };
  if contents.matches("Light").count() == 0 {
      eprintln!("No light(s)");
      chk = 0;
  }

  let mut cnt = 0;
  let objs = vec!["Circle", "Cone", "Cylinder", "Plane"];
  for obj in objs {
    cnt += contents.matches(obj).count();
  }
  if cnt == 0 {
    eprintln!("No object(s)");
    chk = 0;
  }
  chk
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
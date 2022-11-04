use std::{ops::Shr, f32::consts::PI, ffi::CStr};

use libc::{c_int, c_float, c_char};
use sdl2::sys::SDL_Color;

use crate::{vec4_calc::{Vector4, convert_str_to_vec4, calc_unit_v, calc_p_to_v, calc_cross_product}, world::cnt_space, colour::convert_str_to_color};

#[repr(C)]
pub struct Camera {
	pub mode: c_int,
	pub width: c_int,
	pub height: c_int,
	pub dist: c_float,
	pub ar: c_float,
	pub scale: c_float,
	pub xdeg: c_float,
	pub ydeg: c_float,
	pub c: Vector4,
	pub view: Vector4,
	pub up: Vector4,
	pub hor: Vector4,
	pub h_fov: c_float,
	pub v_fov: c_float,
	pub bg: SDL_Color,
}

impl Default for Camera {
    fn default() -> Self {
        Self { mode: Default::default(), width: Default::default(), height: Default::default(), dist: Default::default(), ar: Default::default(), scale: Default::default(), xdeg: Default::default(), ydeg: Default::default(), c: Default::default(), view: Default::default(), up: Default::default(), hor: Default::default(), h_fov: Default::default(), v_fov: Default::default(), bg: SDL_Color { r: 0, g: 0, b: 0, a: 1 } }
    }
}

fn camera_corners(cam: & mut Camera) {
	cam.scale = ((cam.h_fov / 2.) * (PI / 180.)).tan();
	cam.dist = cam.height.shr(1) as f32 / cam.scale;
	cam.ar = cam.width as f32 / cam.height as f32;
	let w: f32 = (cam.width - 1) as f32;
	let h: f32 = (cam.height - 1) as f32;
	cam.ydeg = cam.h_fov * (PI / 180.) / h;
	cam.xdeg = cam.h_fov * (PI / 180.) / w;
	cam.h_fov *= 0.5 * (PI / 180.);
}

pub fn check_camera(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut lines: usize = 1;
	while lines < 5 && (str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric()
  || str.get(*i + lines).unwrap().chars().nth(0).unwrap() == '-')
			 {
				lines += 1;
			}
	if lines != 5
	{
		eprintln!("Error: missing one or more elements in Camera");
		*chk = 0;
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {	
		eprintln!("Camera Error in name");
	}
	if cnt_space(str[*i], i, chk, 2) != 1 {	
		eprintln!("Camera Error in coordinates");
	}
	if cnt_space(str[*i], i, chk, 2) != 1 {	
		eprintln!("Camera Error in screen size angle and fov");
	}
	if cnt_space(str[*i], i, chk, 0) != 1 {	
		eprintln!("Camera Error in camera mode");
	}
	if cnt_space(str[*i], i, chk, 2) != 1 {	
		eprintln!("Camera Error in background color");
	}
}

#[no_mangle]
pub unsafe extern "C" fn ft_camera(str: *const c_char) -> Camera {
  if !str.is_null() {
    let raw = CStr::from_ptr(str);
    return match raw.to_str() {
        Ok(s) => {
          return camera_extraction( s.to_string());
        },
        Err(_) => {
					eprintln!("String Error for Circle");
					Camera::default()
				}
      }
    }
		return Camera::default();
}

fn camera_extraction(str: String) -> Camera
{
	let mut cam = Camera::default();
	cam.c = Vector4{ x: 0., y: 0., z: 0., w: 1.};
	cam.up = Vector4{ x: 0., y: 1., z: 0., w: 0.};
	cam.view = Vector4{ x: 0., y: 0., z: -1., w: 0.};
	cam.hor = Vector4{ x: 1., y: 0., z: 0., w: 0.};
	let s: Vec<&str> = str.split('\n').collect();
	let mut p = Vector4::default();
  convert_str_to_vec4(s.get(2).unwrap(), &mut p);
	unsafe {
		if cam.c.x != p.x || cam.c.y != p.y || cam.c.z != p.z {
			cam.c = p;
			cam.view = calc_unit_v(calc_p_to_v(cam.c, Vector4{ x: 0., y: 0., z: 0., w: 1.}));
			cam.hor = calc_unit_v(calc_cross_product(cam.view,
				Vector4{ x: 0., y: 1., z: 0., w: 0.}));
			cam.up = calc_unit_v(calc_cross_product(cam.hor, cam.view));
		}
	}
	let points: Vec<&str> = s.get(3).unwrap().split(' ').collect();
  cam.width = points.first().unwrap().parse::<i32>().unwrap();
  cam.height = points.get(1).unwrap().parse::<i32>().unwrap();
  cam.h_fov = points.get(2).unwrap().parse::<f32>().unwrap();
  cam.mode = s.get(4).unwrap().parse::<i32>().unwrap();
	convert_str_to_color(s.get(5).unwrap().to_string(), &mut cam.bg);
	camera_corners(&mut cam);
  // TODO map to correct values
	// obj.texmap = props.get(3).unwrap().as_bytes().as_ptr();
	cam
}
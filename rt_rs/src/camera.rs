use std::{ops::Shr, f32::consts::PI};

use libc::{c_int, c_float};
use sdl2::sys::SDL_Color;

use crate::vec4_calc::Vector4;

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

#[no_mangle]
pub extern "C" fn camera_corners(cam: & mut Camera) {
	cam.scale = ((cam.h_fov / 2.) * (PI / 180.)).tan();
	cam.dist = cam.height.shr(1) as f32 / cam.scale;
	cam.ar = cam.width as f32 / cam.height as f32;
	let w: f32 = (cam.width - 1) as f32;
	let h: f32 = (cam.height - 1) as f32;
	cam.ydeg = cam.h_fov * (PI / 180.) / h;
	cam.xdeg = cam.h_fov * (PI / 180.) / w;
	cam.h_fov *= 0.5 * (PI / 180.);
}

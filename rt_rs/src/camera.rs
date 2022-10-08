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
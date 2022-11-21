use std::f32::consts::PI;

use sdl2::sys::SDL_Color;

use crate::{vec4_calc::Vector4, perlin::perlin2d};

#[repr(C)]
pub struct TextureData {
	tex_x: f32,
	tex_y: f32,
	scale_s: f32,
	scale_t: f32,
	s: f32,
	t: f32,
	pattern: f32,
	angle: f32
}

#[no_mangle]
pub unsafe extern "C" fn pattern_init(t: &mut TextureData, n: Vector4) -> SDL_Color
{
	t.scale_s = 10.;
	t.scale_t = 10.;
	t.angle = 0.523599;
	let c = SDL_Color{r: 0, g: 120, b: 80, a: 255};
	t.tex_x = (1. + n.z.atan2(n.x) / PI) * 0.5;
	t.tex_y = n.y.acos() / PI;
	t.s = t.tex_x * t.angle.cos() - t.tex_y * t.angle.sin();
	t.t = t.tex_y * t.angle.cos() + t.tex_x * t.angle.sin();
	c
}

#[no_mangle]
pub unsafe extern "C" fn sepia(mut col:  SDL_Color) -> SDL_Color
{
	col.r = ((col.r as f32 * 0.393) + (col.g as f32 * 0.769) + (col.b as f32 * 0.189)) as u8;
	col.g = ((col.r as f32 * 0.349) + (col.g as f32 * 0.686) + (col.b as f32 * 0.168)) as u8;
	col.b = ((col.r as f32 * 0.272) + (col.g as f32 * 0.534) + (col.b as f32 * 0.131)) as u8;
	col
}

#[no_mangle]
pub unsafe extern "C" fn marble(t: & mut TextureData, n: Vector4) -> SDL_Color
{

	let c = SDL_Color{r: 52, g: 67, b: 62, a: 255};
	t.scale_s = 100.;
	let noise = perlin2d(t.scale_s * 0.5 * n.y, t.scale_t * 0.5 * n.x, 0.1, 4);
	t.angle = 0.523599;
	t.s = t.tex_x * t.angle.cos() - t.tex_y * t.angle.sin();
	t.pattern = modulo(t.s * t.scale_s * noise);
	c
}

#[no_mangle]
pub unsafe extern "C" fn modulo(f: f32) -> f32
{
	if (f - f.floor()) < 0.5 {
    1.
  } else {
    0.
  }
}

#[no_mangle]
pub unsafe extern "C" fn checker(mut t: TextureData) -> f32
{
	t.angle = 1.5708;
	t.s = t.tex_x * t.angle.cos() - t.tex_y * t.angle.sin();
	t.t = t.tex_y * t.angle.cos() + t.tex_x * t.angle.sin();
	t.pattern = modulo(t.s * t.scale_s).powf(modulo(t.t * t.scale_t));
	t.pattern
}
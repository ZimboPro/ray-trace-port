use std::{ops::{Shr}, ffi::CStr};

use libc::{c_char, c_float};
use sdl2::sys::SDL_Color;

pub fn blend_colours(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
    // a.overlay(b)
}

pub fn dim_color(a: &SDL_Color, d: f32) -> SDL_Color {
    SDL_Color {
        r: (a.r as f32 * d) as u8,
        g: (a.g as f32 * d) as u8,
        b: (a.b as f32 * d) as u8,
        a: 255,
    }
}

pub fn mix_color(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
}

pub fn convert_str_to_color(s: String, vec: &mut SDL_Color) {
    let points: Vec<&str> = s.split(' ').collect();
    vec.r = points.first().unwrap().parse::<u8>().unwrap();
    vec.g = points.get(1).unwrap().parse::<u8>().unwrap();
    vec.b = points.get(2).unwrap().parse::<u8>().unwrap(); 
}
pub fn color_adjust(mut a: SDL_Color, mut d: c_float) -> SDL_Color {
    d *= 100.;
    let mut s: u16 = d as u16;
    s *= a.r as u16;
    a.r = (s / 100) as u8;
    let mut s: u16 = d as u16;
    s *= a.g as u16;
    a.g = (s / 100) as u8;
    let mut s: u16 = d as u16;
    s *= a.b as u16;
    a.b = (s / 100) as u8;
	a
}
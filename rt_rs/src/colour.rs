use std::{ops::{Shr}, ffi::CStr};

use libc::c_char;
use sdl2::sys::SDL_Color;

#[no_mangle]
pub unsafe extern "C" fn blend_colours(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
    // a.overlay(b)
}

#[no_mangle]
pub unsafe extern "C" fn dim_color(a: &SDL_Color, d: f32) -> SDL_Color {
    SDL_Color {
        r: (f32::from(a.r) * d).to_int_unchecked(),
        g: (f32::from(a.g) * d).to_int_unchecked(),
        b: (f32::from(a.b) * d).to_int_unchecked(),
        a: 255,
    }
}

#[no_mangle]
pub unsafe extern "C" fn mix_color(a: SDL_Color, b: SDL_Color) -> SDL_Color {
    SDL_Color {
        r: a.r.shr(1) + b.r.shr(1),
        g: a.g.shr(1) + b.g.shr(1),
        b: a.b.shr(1) + b.b.shr(1),
        a: 255,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_map_to_color(val: *const c_char, vec: &mut SDL_Color) {
    if !val.is_null() {
        let raw = CStr::from_ptr(val);
        return match raw.to_str() {
            Ok(s) => {
                convert_str_to_color(s.to_string(), vec);
            }
            Err(_) => {
                eprintln!("Failed to convert string");
                vec.r = 0;
                vec.g = 0;
                vec.b = 0;
            },
        };
    }
    eprintln!("String is null");
    vec.r = 0;
    vec.g = 0;
    vec.b = 0;
}

pub fn convert_str_to_color(s: String, vec: &mut SDL_Color) {
    let points: Vec<&str> = s.split(' ').collect();
    vec.r = points.first().unwrap().parse::<u8>().unwrap();
    vec.g = points.get(1).unwrap().parse::<u8>().unwrap();
    vec.b = points.get(2).unwrap().parse::<u8>().unwrap(); 
}
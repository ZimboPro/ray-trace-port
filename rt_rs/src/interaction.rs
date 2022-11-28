use libc::c_int;
use sdl2::{sys::{SDL_Event, SDL_Keysym}, event::Event};
use sdl2::keyboard::Keycode;

use crate::camera::{Camera, update_view, update_pos};

pub fn ft_eventloop(event: Event, looping: &mut c_int, camera: &mut Camera, draw: &mut c_int)
{
	match event {
    Event::Quit { .. } | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
		*looping = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::W), .. } | Event::KeyDown { keycode: Some(Keycode::Up), .. } => {
		update_view(camera, 0);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::s), .. } | Event::KeyDown { keycode: Some(Keycode::Down), .. } => {
		update_view(camera, 1);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::a), .. } | Event::KeyDown { keycode: Some(Keycode::Left), .. } => {
		update_view(camera, 2);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::d), .. } | Event::KeyDown { keycode: Some(Keycode::Right), .. } => {
		update_view(camera, 3);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::KpPlus), .. } => {
		update_view(camera, 4);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::KpMinus), .. } => {
		update_view(camera, 5);
		*draw = 0;
    },
    	_ => {}
}
}

pub fn mouse_click(camera: &mut Camera, draw: & mut c_int, event: Event)
{
	match event {
    	Event::MouseMotion { x, y, xrel, yrel, .. } => {
			if x >= 20 && y >= 20 && x <= 70 && y <= 70 {
				update_pos(camera, draw, 0);
  		} else if x >= 20 && y >= 90 && x <= 70 && y <= 115 {
				update_pos(camera, draw, 1);
  		}
    	},
    	_ => {}
}
}
use libc::c_int;
use sdl2::{event::Event};
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
    	Event::KeyDown { keycode: Some(Keycode::S), .. } | Event::KeyDown { keycode: Some(Keycode::Down), .. } => {
		update_view(camera, 1);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::A), .. } | Event::KeyDown { keycode: Some(Keycode::Left), .. } => {
		update_view(camera, 2);
		*draw = 0;
    },
    	Event::KeyDown { keycode: Some(Keycode::D), .. } | Event::KeyDown { keycode: Some(Keycode::Right), .. } => {
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
	if let Event::MouseMotion { x, y,   .. } = event {
	    if x >= 20 && y >= 20 && x <= 70 && y <= 70 {
	        update_pos(camera, draw, 0);
	  } else if x >= 20 && y >= 90 && x <= 70 && y <= 115 {
	        update_pos(camera, draw, 1);
	  }
	}
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
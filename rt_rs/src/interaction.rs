use libc::c_int;
use sdl2::sys::{SDL_Event, SDL_Keysym};

use crate::camera::{Camera, update_view, update_pos};

#[no_mangle]
pub unsafe extern "C" fn ft_eventloop(event: SDL_Event, looping: &mut c_int, camera: &mut Camera, draw: &mut c_int)
{
	if event.type_ == 256 {
		*looping = 0;
  }
	else if event.key.keysym.sym == 27 {
		*looping = 0;
  }
	else if event.key.keysym.sym == 119 {
		update_view(camera, 0);
		*draw = 0;
	} else if event.key.keysym.sym == 115 {
		update_view(camera, 1);
		*draw = 0;
	} else if event.key.keysym.sym == 97 {
		update_view(camera, 2);
		*draw = 0;
	} else if event.key.keysym.sym == 100 {
		update_view(camera, 3);
		*draw = 0;
	} else if event.key.keysym.sym == 1073741906 {
		update_pos(camera, draw, 0);
  } else if event.key.keysym.sym == 1073741905 {
		update_pos(camera, draw, 1);
  } else if event.key.keysym.sym == 1073741904 {
		update_pos(camera, draw, 2);
  } else if event.key.keysym.sym == 1073741903 {
		update_pos(camera, draw, 3);
  } else if event.key.keysym.sym == 1073741911 {
		update_pos(camera, draw, 4);
  } else if event.key.keysym.sym == 1073741910 {
		update_pos(camera, draw, 5);
  }
}

#[no_mangle]
pub unsafe extern "C" fn mouse_click(camera: &mut Camera, draw: & mut c_int, event: SDL_Event)
{
	let x = event.motion.x;
	let y = event.motion.y;
	if x >= 20 && y >= 20 && x <= 70 && y <= 70 {
		update_pos(camera, draw, 0);
  } else if x >= 20 && y >= 90 && x <= 70 && y <= 115 {
		update_pos(camera, draw, 1);
  }
}
use libc::{c_int, c_uint};
use sdl2::sys::{SDL_Surface, SDL_BYTEORDER, SDL_BIG_ENDIAN};

#[repr(C)]
pub struct Pixel {
  pub x: c_int,
  pub y: c_int,
}


// pub fn get_pixel(surf: & SDL_Surface,  x: c_int, y: c_int) -> c_uint
// {
//   let mut bpp = 0;
//   unsafe {

//     bpp = (*surf.format).BytesPerPixel.clone();
//   }
// 	let p: c_uint = surf.pixels.into() + y * surf.pitch + x * bpp.into();
// 	if bpp == 1 {
// 		return p;
//   }
// 	else if bpp == 2 {
// 		return p;
//   }
// 	else if bpp == 3
// 	{
// 		if SDL_BYTEORDER == SDL_BIG_ENDIAN {
//       let t = transform_u32_to_array_of_u8(p);
// 			return  (t[0] << 16 | t[1] << 8 | t[2]).into();
//     }
// 		else {
//       let t = transform_u32_to_array_of_u8(p);
// 			return (t[0] | t[1] << 8 | t[2] << 16).into();
//     }
// 	}
// 	return p
// }

// fn transform_u32_to_array_of_u8(x:u32) -> [u8;4] {
//   let b1 : u8 = ((x >> 24) & 0xff) as u8;
//   let b2 : u8 = ((x >> 16) & 0xff) as u8;
//   let b3 : u8 = ((x >> 8) & 0xff) as u8;
//   let b4 : u8 = (x & 0xff) as u8;
//   return [b1, b2, b3, b4]
// }
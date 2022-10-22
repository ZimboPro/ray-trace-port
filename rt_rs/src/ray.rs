use libc::c_float;

use crate::{vec4_calc::{Vector4, calc_addition, calc_multi, calc_vect_to_point}, camera::Camera};

#[repr(C)]
#[derive(Default)]
pub struct Ray {
  sc: Vector4,
	v: Vector4
}

#[no_mangle]
pub extern "C" fn ray(obj: Camera, x: c_float, y: c_float) -> Ray
{
	let	mut ray = Ray::default();

	let x = (-obj.h_fov + x * obj.xdeg) * obj.ar;
	let y = obj.h_fov - y * obj.ydeg;
  unsafe {
    ray.v = calc_addition(calc_multi(obj.view, x.cos()), calc_multi(
          obj.hor, x.sin()));
    ray.v = calc_addition(calc_multi(ray.v, y.cos()), calc_multi(obj.up,
            y.sin()));
    ray.sc = calc_vect_to_point(obj.c, ray.v, obj.dist);
  }
	ray
}
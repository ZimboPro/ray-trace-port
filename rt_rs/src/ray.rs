use libc::c_float;

use crate::{vec4_calc::{Vector4, calc_addition, calc_multi, calc_vect_to_point}, camera::Camera, circle::int_circle, cone::{int_cone, cone_norm}, cylinder::{int_cyl, cyl_norm}, plane::int_plane, object::{ObjectType, ObjectItem}};

#[repr(C)]
#[derive(Default)]
pub struct Ray {
  pub sc: Vector4,
	pub v: Vector4
}

#[derive(Default)]
pub struct Quad {
  pub a: c_float,
  pub b: c_float,
  pub c: c_float,
  pub t1: c_float,
  pub t2: c_float,
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

#[no_mangle]
pub unsafe extern "C" fn intersect(obj: ObjectItem, d: &mut c_float, ray: Ray) {
  if obj.r#type == ObjectType::Circle {
    int_circle(obj, d, ray);
  } else if obj.r#type == ObjectType::Cone {
    int_cone(obj, d, ray);
  } else if obj.r#type == ObjectType::Cylinder {
    int_cyl(obj, d, ray);
  } else if obj.r#type == ObjectType::Plane {
    int_plane(obj, d, ray);
  }
}


#[no_mangle]
pub unsafe extern "C" fn normal(obj: ObjectItem, d: c_float, ray: Ray) -> Vector4 {
  return if obj.r#type == ObjectType::Cylinder {
    cyl_norm(obj, d, ray)
  } else {
    cone_norm(obj, d, ray)
  };
}
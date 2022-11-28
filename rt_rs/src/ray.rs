use libc::c_float;
use sdl2::{sys::{SDL_Init, SDL_INIT_EVERYTHING, SDL_CreateWindow, Window}, render::Canvas};

use crate::{vec4_calc::{Vector4, calc_addition, calc_multi, calc_vect_to_point}, camera::Camera, circle::int_circle, cone::{int_cone, cone_norm}, cylinder::{int_cyl, cyl_norm}, plane::int_plane, object::{ObjectType, ObjectItem, World}};

#[repr(C)]
#[derive(Default, Clone, Copy)]
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
    ray.v = calc_addition(calc_multi(obj.view, x.cos()), calc_multi(
          obj.hor, x.sin()));
    ray.v = calc_addition(calc_multi(ray.v, y.cos()), calc_multi(obj.up,
            y.sin()));
    ray.sc = calc_vect_to_point(obj.c, ray.v, obj.dist);
	ray
}

pub fn intersect(obj: ObjectItem, d: &mut c_float, ray: Ray) {
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


pub fn normal(obj: ObjectItem, d: c_float, ray: Ray) -> Vector4 {
  if obj.r#type == ObjectType::Cylinder {
    cyl_norm(obj, d, ray)
  } else {
    cone_norm(obj, d, ray)
  }
}

fn find_sdl_gl_driver() -> Option<u32> {
  for (index, item) in sdl2::render::drivers().enumerate() {
      if item.name == "opengl" {
          return Some(index as u32);
      }
  }
  None
}

pub fn raytrace(obj: &mut World) {

  let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let window = video_subsystem.window("RT", obj.camera.width, obj.camera.height)
        .opengl() // this line DOES NOT enable opengl, but allows you to create/get an OpenGL context from your window.
        .build()
        .unwrap();
    let mut canvas = window.into_canvas()
        .index(find_sdl_gl_driver().unwrap())
        .build()
        .unwrap();
    events(&mut canvas, &mut obj);
}

fn events(ren:&mut  Canvas<Window>, obj: &mut World) {
 let mut r#loop = 1;
 let mut draw = 0;
 while r#loop == 1 {
  if draw == 0 {
    if obj.camera.mode == 0 {
      normal_draw();
    }
    // else {
    //   cartoon_draw();
    // }
    draw = 1;
  }
 }
}
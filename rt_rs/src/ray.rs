use libc::c_float;
use sdl2::{sys::{SDL_Init, SDL_CreateWindow, }, render::{WindowCanvas}, event::Event};
use sdl2::keyboard::Keycode;
use crate::{vec4_calc::{Vector4, calc_addition, calc_multi, calc_vect_to_point}, camera::Camera, circle::int_circle, cone::{int_cone, cone_norm}, cylinder::{int_cyl, cyl_norm}, plane::int_plane, object::{ObjectType, ObjectItem, World}, interaction::{ft_eventloop, mouse_click}};

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
    events(&mut canvas, obj, &sdl_context);
}

fn events(ren:&mut WindowCanvas, obj: &mut World, sdl_context: & sdl2::Sdl) {
 let mut r#loop = 1;
 let mut draw = 0;
 let mut event_pump = sdl_context.event_pump().unwrap();
 while r#loop == 1 {
  if draw == 0 {
    if obj.camera.mode == 0 {
      normal_draw(ren, obj);
    } else {
      cartoon_draw(ren, obj);
    }
    draw = 1;
  }
  for event in event_pump.poll_iter() {
    match event {
      Event::Quit { .. } | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
        r#loop = 0;
      },
      _ => {
        if event.is_mouse() {
          mouse_click(&mut obj.camera, &mut draw, event);
        } else if event.is_keyboard() {
        ft_eventloop(event, &mut r#loop, &mut obj.camera, &mut draw);
}
      }
    }
  }
 }
}

fn normal_draw(ren:&mut WindowCanvas, obj: &mut World) {
  
}

fn cartoon_draw(ren:&mut WindowCanvas, obj: &mut World) {
  
}
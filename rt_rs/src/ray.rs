use std::{time::Duration, ops::{Shr}};

use libc::c_float;
use rayon::prelude::{IntoParallelRefMutIterator, ParallelIterator};
use sdl2::{render::{WindowCanvas}, event::Event, rect::Point};
use sdl2::keyboard::Keycode;
use crate::{vec4_calc::{Vector4, calc_addition, calc_multi, calc_vect_to_point}, camera::Camera, circle::int_circle, cone::{int_cone, cone_norm}, cylinder::{int_cyl, cyl_norm}, plane::int_plane, object::{ObjectType, ObjectItem, World}, interaction::{ft_eventloop, mouse_click}, pixel::{RenderPixel}, colour::{color_adjust, mix_color, get_cartoon_color}, reflection::get_reflect_ray, fresnel::{fresnel_effect, fresnel_effect_cart}};
use sdl2::sys::SDL_Color;
use crate::colour::get_color;


const DEPTH: usize = 10;
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

pub fn ray(obj: Camera, x: c_float, y: c_float) -> Ray
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
  } else if obj.is_plane() {
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

pub fn raytrace(obj: &mut World, is_aa: bool) {

  let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let window = video_subsystem.window("RT", obj.camera.width as u32, obj.camera.height as u32)
        .opengl() // this line DOES NOT enable opengl, but allows you to create/get an OpenGL context from your window.
        .build()
        .unwrap();
    let mut canvas = window.into_canvas()
        .index(find_sdl_gl_driver().unwrap())
        .build()
        .unwrap();
    events(&mut canvas, obj, &sdl_context, is_aa);
}

fn events(ren:&mut WindowCanvas, obj: &mut World, sdl_context: & sdl2::Sdl, is_aa: bool) {
 let mut r#loop = 1;
 let mut draw = 0;
 let mut event_pump = sdl_context.event_pump().unwrap();
 let mut canvas = init_canvas_array(obj);
 
 while r#loop == 1 {
  if draw == 0 {
        if obj.camera.mode == 0 {
            normal_draw(ren, obj, &mut canvas, is_aa);
        } else {
            cartoon_draw(ren, obj, &mut canvas, is_aa);
        }
    draw = 1;
  }
  ren.set_draw_color(obj.camera.bg);
  draw_screen(ren, &mut canvas);
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
  ::std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 60));
 }
}

fn init_canvas_array(obj: & World) -> Vec<RenderPixel> {
  let mut v = Vec::with_capacity((obj.camera.width * obj.camera.height) as usize);
  for y in 0..obj.camera.height as usize {
    for x in 0..obj.camera.width as usize {
      v.push(RenderPixel::new(x, y));
    }
  }
  v
}

fn normal_draw(_ren:&mut WindowCanvas, obj: &mut World, canvas: & mut Vec<RenderPixel>, is_aa: bool) {
  let k = obj.camera;
  assert!(!obj.lights.is_empty(), "Needs to be at least one light");
  canvas.par_iter_mut().for_each(|p| {
    if !is_aa {
        let rv = ray(k, p.p.x as c_float, p.p.y as c_float);
    let mut c = obj.clone();
        assert!(!c.lights.is_empty(), "Needs to be at least one light");
        let mut d = 0.;
        p.c = trace_ray(&mut c, rv, 0/*, ren*/, &mut d);
    } else {
        let rv_0 = ray(k, p.p.x as c_float - 0.25, p.p.y as c_float - 0.25);
        let rv_1 = ray(k, p.p.x as c_float + 0.25, p.p.y as c_float - 0.25);
        let rv_2 = ray(k, p.p.x as c_float - 0.25, p.p.y as c_float + 0.25);
        let rv_3 = ray(k, p.p.x as c_float + 0.25, p.p.y as c_float + 0.25);
        let mut c = obj.clone();
        assert!(!c.lights.is_empty(), "Needs to be at least one light");
        let mut d = 0.;
        p.c = trace_ray(&mut c, rv_0, 0/*, ren*/, &mut d);
        let t = trace_ray(&mut c, rv_1, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
        let t = trace_ray(&mut c, rv_2, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
        let t = trace_ray(&mut c, rv_3, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
    }
  });
}

fn draw_screen(ren:&mut WindowCanvas, canvas: & mut [RenderPixel]) {
  ren.clear();
  canvas.iter().for_each(|p| {
    ren.set_draw_color(p.c);
    if let Err(e) = ren.draw_point::<Point>(p.p.into()) {
      eprintln!("Draw error {}", e);
    }
  });
  ren.present();
}

fn cartoon_draw(_ren:&mut WindowCanvas, obj: &mut World, canvas: & mut Vec<RenderPixel>,is_aa: bool) {
  let k = obj.camera;
  canvas.par_iter_mut().for_each(|p| {
    if !is_aa {
        let rv = ray(k, p.p.x as c_float, p.p.y as c_float);
        let mut c = obj.clone();
        assert!(!c.lights.is_empty(), "Needs to be at least one light");
        let mut d = 0.;
        p.c = trace_ray_cart(&mut c, rv, 0/*, ren*/, &mut d);
    } else {
        let rv_0 = ray(k, p.p.x as c_float - 0.25, p.p.y as c_float - 0.25);
        let rv_1 = ray(k, p.p.x as c_float + 0.25, p.p.y as c_float - 0.25);
        let rv_2 = ray(k, p.p.x as c_float - 0.25, p.p.y as c_float + 0.25);
        let rv_3 = ray(k, p.p.x as c_float + 0.25, p.p.y as c_float + 0.25);
        let mut c = obj.clone();
        assert!(!c.lights.is_empty(), "Needs to be at least one light");
        let mut d = 0.;
        p.c = trace_ray_cart(&mut c, rv_0, 0/*, ren*/, &mut d);
        let t = trace_ray_cart(&mut c, rv_1, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
        let t = trace_ray_cart(&mut c, rv_2, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
        let t = trace_ray_cart(&mut c, rv_3, 0/*, ren*/, &mut d);
        p.c = mix_color(p.c, t);
    }
  });
}

pub fn trace_ray(obj:&mut World, ray: Ray, depth: usize/*, ren: & mut WindowCanvas*/, d: &mut f32) -> SDL_Color {
  if depth < DEPTH
	{
	  let i = intersection(obj, d, ray.v, ray.sc);
	  if i != -1 {
      let mut p_c = get_color(obj/*, ren*/, i as usize, ray, d);
      let f = obj.objects[i as usize].reflect;
      if obj.objects[i as usize].reflect > 0. && !obj.objects[i as usize].is_refracted()
      {
        let temp = get_reflect_ray(obj.objects[i as usize], ray, *d);
        let rlc =
        color_adjust(trace_ray(obj, temp, depth + 1/*, ren*/, d), f);
        p_c = mix_color(rlc, p_c);
      }
      if obj.objects[i as usize].is_refracted()
      {
        obj.i = i as usize;
        let rlc = fresnel_effect(obj, ray, depth/*, ren*/, d);
        p_c = SDL_Color{r: (rlc.r as f32 * f + p_c.r  as f32 * (1. - f)) as u8, g: (rlc.g  as f32 * f
          + p_c.g  as f32 * (1. - f)) as u8, b: (rlc.b  as f32 * f + p_c.b  as f32 * (1. - f)) as u8, a: 255};
        }
        return p_c;
      }
    }
	obj.camera.bg
}

pub fn trace_ray_cart(obj:&mut World, ray: Ray, depth: usize/*, ren: & mut WindowCanvas*/, d: &mut f32) -> SDL_Color {
  if depth < DEPTH
	{
	  let i = intersection(obj, d, ray.v, ray.sc);
	  if i == -1 {
	    return obj.camera.bg;
	  }
		let mut p_c = get_cartoon_color(obj/*, ren*/, i as usize, ray, d);
		let f = obj.objects[i as usize].reflect;
		
		if obj.objects[i as usize].reflect > 0. && !obj.objects[i as usize].is_refracted()
		{
			let temp = get_reflect_ray(obj.objects[i as usize], ray, *d);
			let rlc =
			color_adjust(trace_ray_cart(obj, temp, depth + 1/*, ren*/, d), f);
			p_c = SDL_Color{
        r: rlc.r.shr(1) + p_c.r.shr(1),
        g: rlc.g.shr(1) + p_c.g.shr(1),
        b: rlc.b.shr(1) + p_c.b.shr(1),
        a: 255};
      // assert!(!(p_c.r == 0 && p_c.g == 0 && p_c.b == 0));
		}
		if obj.objects[i as usize].is_refracted()
		{
			obj.i = i as usize;
			let rlc = fresnel_effect_cart(obj, ray, depth/*, ren*/, d);
			p_c = SDL_Color{
        r: (rlc.r as f32 * f + p_c.r  as f32 * (1. - f)) as u8,
        g: (rlc.g as f32 * f + p_c.g  as f32 * (1. - f)) as u8,
        b: (rlc.b as f32 * f + p_c.b  as f32 * (1. - f)) as u8,
        a: 255};
		}
		return p_c;
	}
	obj.camera.bg
}

pub fn intersection(obj: & mut World, d: &mut f32, v: Vector4, p: Vector4) -> i32
{
	*d = -1.;
	let mut i = 0;
	let mut ind = -1;
	let ray = Ray{sc: p, v};
	while i < obj.obj_total
	{
		let mut dist = -1.;
		intersect(obj.objects[i], &mut dist, ray);
		if dist != -1. && (dist < *d || *d == -1.)
		{
		    *d = dist;
			ind = i as i32;
		}
		i += 1;
	}
	ind
}

#[cfg(test)]
mod tests {
    use std::fs;

    use crate::{object::{objects, ObjectType}, ray::{ray, trace_ray_cart, trace_ray, intersection, Ray}, colour::get_color, vec4_calc::{calc_vect_to_point, calc_p_to_v, calc_unit_v}, light::light_color};


    #[test]
    fn ray_1() {
      let contents = fs::read_to_string("/home/leslie/sandbox/rust/ray-trace-port/rt_orig/cylinder_1").unwrap();
      let mut obj = objects(&contents);
      let rv = ray(obj.camera, 160., 200.);
      assert!(!obj.lights.is_empty(), "Needs to be at least one light");
      let mut d = 0.;
      let col = trace_ray(&mut obj, rv, 0/*, ren*/, &mut d);
      assert!(col.r == 0, "R = {}", col.r);
      assert!(col.g == 191, "g = {}", col.g);
      assert!(col.b == 0, "b = {}", col.b);
    }

    #[test]
    fn intersection1() {
      let contents = fs::read_to_string("/home/leslie/sandbox/rust/ray-trace-port/rt_orig/cylinder_1").unwrap();
      let mut obj = objects(&contents);
      let rv = ray(obj.camera, 160., 100.);
      assert!(!obj.lights.is_empty(), "Needs to be at least one light");
      let mut d = 0.;
      let i = intersection(&mut obj, &mut d,rv.v, rv.sc);
      let col = get_color(&mut obj, i as usize, rv, &mut d);
      assert!(col.r == 0, "R = {}", col.r);
      assert!(col.g == 255, "g = {}", col.g);
      assert!(col.b == 255, "b = {}", col.b);
    }

    #[test]
    fn intersection2() {
      let contents = fs::read_to_string("/home/leslie/sandbox/rust/ray-trace-port/rt_orig/cylinder_1").unwrap();
      let mut obj = objects(&contents);
      let rv = ray(obj.camera, 160., 200.);
      assert!(!obj.lights.is_empty(), "Needs to be at least one light");
      let mut d = 0.;
      let i = intersection(&mut obj, &mut d,rv.v, rv.sc);
      let col = get_color(&mut obj, i as usize, rv, &mut d);
      assert!(i == 2, "i = {}", i);
      assert!(obj.objects[i as usize].r#type != ObjectType::Plane, "Type = {}", obj.objects[i as usize].r#type);
      assert!(obj.objects[i as usize].r#type == ObjectType::Circle, "Type = {}", obj.objects[i as usize].r#type);
      assert!(obj.objects[i as usize].r#type != ObjectType::Cylinder, "Type = {}", obj.objects[i as usize].r#type);
      
      let pt = calc_vect_to_point(rv.sc, rv.v, d * 0.995);
      assert!(pt.x == -7117.7065, "X = {}", pt.x);
      assert!(pt.y == -22.997763, "Y = {}", pt.y);
      assert!(pt.z == -16014.878, "Z = {}", pt.z);
      assert!(pt.w == 1., "W = {}", pt.w);
      let n = calc_unit_v(calc_p_to_v(obj.objects[i as usize].c, pt));
      assert!(n.x == 0.9288683, "X = {}", n.x);
      assert!(n.y == -0.0065235174, "Y = {}", n.y);
      assert!(n.z == 0.37035283, "Z = {}", n.z);
      assert!(n.w == 0., "W = {}", n.w);
      let c = light_color(&mut obj, Ray { sc: pt, v: n}, i as usize, & mut d);
      assert!(c.r == 0, "light R = {}", c.r);
      assert!(c.g == 191, "light G = {}", c.g);
      assert!(c.b == 0, "light B = {}", c.b);
      assert!(col.r == 0, "R = {}", col.r);
      assert!(col.g == 191, "g = {}", col.g);
      assert!(col.b == 0, "b = {}", col.b);
    }
}
use glam::{self, f32};
use libc::{c_float, c_int};
use sdl2::sys::SDL_Color;
use serde::{Deserialize, Serialize};

use crate::{vec4_calc::{Vector4, calc_multi}, camera::{Camera, camera_extraction}, light::{Light, lights}, circle::{circle_extraction}, cone::cone_extraction, cylinder::cylinder_extraction, plane::plane_extraction, vec3_calc::calc_multi_vec};

#[repr(C)]
#[derive(Serialize, Deserialize, PartialEq, Eq, Clone, Copy)]
pub enum ObjectType {
    Circle,
    Cylinder,
    Cone,
    Plane,
    Texture,
}

impl Default for ObjectType {
    fn default() -> Self {
        ObjectType::Circle
    }
}

#[repr(C)]
#[derive(Serialize, Deserialize, Default)]
pub struct Color {
    r: u8,
    g: u8,
    b: u8
}

impl From<SDL_Color> for Color {
    fn from(col: SDL_Color) -> Self {
        Self { r: col.r, g: col.g, b: col.b }
    }
}

impl Into<SDL_Color> for Color {
    fn into(self) -> SDL_Color {
        SDL_Color { r: self.r, g: self.g, b: self.b, a: 255 }
    }
}

#[repr(C)]
#[derive(Default, Serialize, Deserialize)]
pub struct Vec3 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

impl From<glam::f32::Vec3> for Vec3 {
    fn from(v: glam::f32::Vec3) -> Self {
        Self { x: v.x, y: v.y, z: v.z }
    }
}


#[repr(C)]
#[derive(Serialize, Deserialize)]
pub struct Vec4 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
    pub w: f32,
}

impl From<glam::f32::Vec4> for Vec4 {
    fn from(v: glam::f32::Vec4) -> Self {
        Self { x: v.x, y: v.y, z: v.z, w: v.w }
    }
}

#[repr(C)]
#[derive(Serialize, Deserialize, Default)]
pub struct Object {
    pub obj_type: ObjectType,
    pub pnt: glam::f32::Vec3,
    pub dir: glam::f32::Vec4,
    pub color: Color,
    pub height: f32,
    pub radius: f32,
    pub reflect: f32,
    pub refract: i32,
    pub pattern: i32,
    pub filter: f32,
}

#[repr(C)]
pub struct WorldObject {
    pub obj_type: ObjectType,
    pub pnt: Vec3,
    pub dir: Vec4,
    pub color: SDL_Color,
    pub height: f32,
    pub radius: f32,
    pub reflect: f32,
    pub refract: i32,
    pub pattern: i32,
    pub filter: f32,
}

impl From<Object> for WorldObject {
    fn from(obj: Object) -> Self {
        Self {
            obj_type: obj.obj_type,
            pnt: obj.pnt.into(),
             dir: obj.dir.into(),
             color: obj.color.into(),
             height: obj.height,
             radius: obj.radius,
             reflect: obj.reflect,
             refract: obj.refract,
             pattern: obj.pattern,
             filter: obj.filter,
         }
    }
}

#[repr(C)]
#[derive(Clone, Copy)]
pub struct	ObjectItem
{
    pub r#type: ObjectType,
    pub c: Vector4,
    pub h: c_float,
    pub rad: c_float,
    pub col: SDL_Color,
    pub dir: Vector4,
    pub reflect: c_float,
    pub refract: c_int,
    pub pattern: c_int,
    pub filter: c_int,
}

impl ObjectItem {
    pub fn new() -> Self {
        Self {
            r#type: Default::default(),
            c: Default::default(),
            h: Default::default(),
            rad: Default::default(),
            col: SDL_Color { r: 0, g: 0, b: 0, a: 255 },
            dir: Default::default(),
            reflect: Default::default(),
            refract: Default::default(),
            pattern: Default::default(),
            filter: Default::default()
        }
    }
}

impl Default for ObjectItem {
    fn default() -> Self {
        Self::new()
    }
}

pub struct World {
    pub d: f32,
    pub obj_total: usize,
    pub light: usize,
    pub progress: i32,
    pub first: i32,
    pub objects: Vec<ObjectItem>,
    pub camera: Camera,
    pub lights: Vec<Light>,
    pub i: usize
}

impl World {
    pub fn new() -> Self {
        Self {
            d: 0.,
            obj_total: 0,
            light: 0,
            progress: 0,
            first: 0,
            objects: Vec::new(),
            camera: Camera::default(),
            lights: Vec::new(),
            i: 0
        }
    }
}

pub fn objects(file_contents: &str) -> World {
    let splits = file_contents.split("\n\n");
    let mut w = World::new();
    for s in splits {
        if s.contains("Circle") {
            w.objects.push(circle_extraction(s));
        } else if s.contains("Cone") {
            w.objects.push(cone_extraction(s));
        } else if s.contains("Cylinder") {
            w.objects.push(cylinder_extraction(s));
        } else if s.contains("Plane") {
            w.objects.push(plane_extraction(s));
        } else if s.contains("Lights") {
            lights(s, &mut w.lights);
        } else if s.contains("Camera") {
            w.camera = camera_extraction(s);
        }
    }
    w.obj_total = w.objects.len();
    update_map(&mut w);
    w
}

fn update_map(obj: &mut World)
{
    for object in &mut obj.objects {
		if object.r#type == ObjectType::Plane {
			object.dir.w *= obj.camera.dist;
        } else if object.r#type != ObjectType::Plane {
            object.c = calc_multi(object.c, obj.camera.dist);
            object.rad *= obj.camera.dist;
        }
		if object.r#type != ObjectType::Plane && object.r#type != ObjectType::Circle {
			object.h *= obj.camera.dist;
        }
	}
	obj.camera.c = calc_multi(obj.camera.c, obj.camera.dist);
    for light in &mut obj.lights {
        light.c = calc_multi_vec(light.c, obj.camera.dist);
    }
}
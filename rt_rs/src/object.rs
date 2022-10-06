use glam::{self, f32};
use libc::c_char;
use sdl2::sys::SDL_Color;
use serde::{Deserialize, Serialize};

#[repr(C)]
#[derive(Serialize, Deserialize)]
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
#[derive(Serialize, Deserialize)]
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

#[no_mangle]
pub unsafe extern "C" fn parse_file(val: *const c_char) -> WorldObject {
    Object::default().into()
}

#[repr(C)]
pub struct Light {
    pnt: Vec3,
    total: i32,
}

#[no_mangle]
pub unsafe extern "C" fn extact_light(val: *const c_char) -> Light {
    Light {
        pnt: Vec3{
            x: 0.,
            y: 0.,
            z: 0.,
        },
        total: 0,
    }
}
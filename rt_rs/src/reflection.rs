use libc::c_float;

use crate::{object::ObjectItem, ray::Ray, circle::circle_reflection, cylinder::cylinder_reflection, cone::cone_reflection, plane::plane_reflection};

pub fn get_reflect_ray(obj: ObjectItem, ray: Ray, d: c_float) -> Ray
{
	match obj.r#type {
    crate::object::ObjectType::Circle => circle_reflection(obj, ray, d),
    crate::object::ObjectType::Cylinder => cylinder_reflection(obj, ray, d),
    crate::object::ObjectType::Cone => cone_reflection(obj, ray, d),
    crate::object::ObjectType::Plane => plane_reflection(obj, ray, d),
    crate::object::ObjectType::Texture => Ray::default(),
  }
}
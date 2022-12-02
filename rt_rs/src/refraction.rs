use libc::c_float;

use crate::{object::ObjectItem, ray::Ray, circle::circle_refraction, cylinder::cylinder_refraction, cone::cone_refraction, plane::plane_refraction};

pub fn get_refract_ray(obj: ObjectItem, ray: Ray, d: c_float) -> Ray
{
	match obj.r#type {
    crate::object::ObjectType::Circle => circle_refraction(obj, ray, d),
    crate::object::ObjectType::Cylinder => cylinder_refraction(obj, ray, d),
    crate::object::ObjectType::Cone => cone_refraction(obj, ray, d),
    crate::object::ObjectType::Plane => plane_refraction(obj, ray, d),
    crate::object::ObjectType::Texture => Ray::default(),
  }
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
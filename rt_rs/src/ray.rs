use crate::vec4_calc::Vector4;

#[repr(C)]
struct Ray {
  sc: Vector4,
	v: Vector4
}
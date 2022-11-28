use libc::{c_float, c_int};

use crate::vec4_calc::{Vector4, calc_dp};

pub fn fresnel(n1: c_float, n2: c_int, n: Vector4, v: Vector4) -> c_float
{
	let n2t = (n2 as f32) / 1000000.;
	let mut r0 = (n1 - n2t) / (n1 + n2t);
	r0 *= r0;
	let mut c1 = -calc_dp(n, v) as f32;
	if n1 > n2t
	{
		let ret = n1 / n2t;
		let x = ret * ret * (1. - c1 * c1);
		if x > 1. {
			return 1.;
    }
		c1 = (1. - x).sqrt();
	}
	let x = 1. - c1;
	let ret = r0 + (1. - r0) * x * x * x * x * x;
	ret
}
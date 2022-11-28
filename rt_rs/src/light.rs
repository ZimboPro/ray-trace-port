use glam::Vec3;
use libc::c_int;

use crate::{world::cnt_space, vec3_calc::{str_to_vec3_rs}};


#[derive(Default)]
pub struct Light {
	pub total: usize,
	pub c: Vec3
}

pub fn check_light(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut t= cnt_space(str[*i], i, chk, 2);

	if t != 1 {
		eprintln!("Light Error in name");
  }
	else
	{
		let s: Vec<&str> = str[*i - 1].split(' ').collect();
		t = s[1].parse::<i32>().unwrap();
	}
	let mut lines = 1;
	while lines < t.try_into().unwrap() && str.get(*i + lines).unwrap().chars().next().unwrap().is_numeric() {
		lines += 1;
  }
	if lines != t.try_into().unwrap() {
		*chk = 0;
  }
	lines = 0;
	while lines < t.try_into().unwrap()
	{
		if cnt_space(str[*i], i, chk, 2) != 1 {
			eprintln!("Light Error in coordinates");
    }
		lines += 1;
	}
}

pub fn lights(s: &str, lights: &mut Vec<Light>) {
	let l: Vec<&str> = s.split('\n').collect();
	let mut i = 0;
	while !l[i].contains("Light") {
		i +=1;
	}
	while i < l.len() {
		let mut light = Light::default();
		str_to_vec3_rs(l[i], &mut light.c);
		lights.push(light);
		i += 1;
	}
	let total = lights.len();
	for light in lights {
			light.total = total;
	}
}
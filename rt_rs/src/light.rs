use glam::Vec3;
use libc::c_int;
use sdl2::sys::SDL_Color;

use crate::{world::cnt_space, vec3_calc::{str_to_vec3_rs}, object::{World}, colour::{dim_color, AMB}, vec4_calc::{calc_unit_v, calc_dp, calc_p_dist_vec, calc_p_to_vec}, ray::{Ray, intersection}};


#[derive(Default, Clone, Copy)]
pub struct Light {
	pub total: usize,
	pub c: Vec3
}

pub fn check_light(str: &[&str], i: &mut usize, chk: &mut c_int)
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
	while l[i].contains("Light") {
		i +=1;
	}
	while i < l.len() && l.get(i).is_some() {
		if !l[i].is_empty() {
			let mut light = Light::default();
			str_to_vec3_rs(l[i], &mut light.c);
			lights.push(light);
		}
		i += 1;
	}
	let total = lights.len();
	for light in lights {
			light.total = total;
	}
	assert!(total > 0, "There needs to be a light");
}

pub fn light_color(obj: &mut World, n: Ray, i: usize, d: &mut f32) -> SDL_Color
{
	let mut j = 0.;
	let mut t = obj.clone();
	for light in &obj.lights {
			
		let l = calc_unit_v(calc_p_to_vec(n.sc, light.c));
		let mut tmp = 0.;
		if !obj.objects[i].is_plane() {
			tmp = calc_dp(l, n.v);
			if tmp < 0. {
				tmp /= 6.;
			}
		} else if intersection(& mut t, d, l, n.sc) != -1 &&
				calc_p_dist_vec(n.sc, light.c) > *d {
			tmp = 0.;
		} else if obj.objects[i].is_plane() {
			tmp = 1.;
		}
		j += tmp;
	}
	j /= obj.lights.len() as f32;
	dim_color(&obj.objects[i].col, AMB + (1. - AMB) * j)
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
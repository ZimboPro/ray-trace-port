






// #[no_mangle]
// pub unsafe extern "C" fn cartoon_cone(obj: ObjectItem, col: & mut SDL_Color, i: c_int, rv: Ray)
// {

// 	let mut p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 1.05));
// 	let mut di = -1.;
//   let r = Ray{sc: p.clone(), v: rv.v.clone()};
// 	int_cone(obj, &mut di, r);
// 	if di == -1. {
//     col = &mut SDL_Color{ r: 0, g: 0, b: 0, a: 255};
//   }
// 	else
// 	{
// 		p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
// 		di = calc_p_dist(p, obj.c).powf(2.) / calc_dp(
// 				calc_p_to_v(obj.c, p),
// 				calc_unit_v(obj.dir));
// 		let n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c,
// 					obj.dir, di), p));
//     let r = Ray{sc: p, v: n};
// 		*col = cartoon_color(obj, r, i);
// 	}
// }

use sdl2::sys::SDL_Color;

use crate::{colour::{AMB, dim_color}, object::{World}, ray::{Ray, intersection}, vec4_calc::{calc_unit_v, calc_p_to_vec, calc_dp, calc_p_dist_vec}};

fn cartoon_help(col: SDL_Color, j: f32) -> SDL_Color
{
	dim_color(&col, AMB + (1. - AMB) * j)
}

pub fn cartoon_color(obj: &mut World, n: Ray, i: usize, d: &mut f32) -> SDL_Color
{
	let mut j = 0.;
	let mut t = obj.clone();
	for light in &obj.lights {
		let l = calc_unit_v(calc_p_to_vec(n.sc, light.c));
		let mut tmp = calc_dp(l, n.v);
		if (!obj.objects[i].is_plane() && tmp < 0.)
			|| (intersection(&mut t, d, l, n.sc) != -1 &&
				calc_p_dist_vec(n.sc, light.c) > *d) {
			tmp = 0.;	
		} else if obj.objects[i].is_plane() {
			tmp = 1.;
		}
		else if tmp < 0.5 {
			tmp = 0.5;
		}
		else {
			tmp = 1.;
		}
		j += tmp;
	}
	j /= obj.lights.len() as f32;
	cartoon_help(obj.objects[i].col, j)
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
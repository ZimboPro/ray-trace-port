






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
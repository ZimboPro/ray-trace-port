/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 16:02:03 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 16:00:04 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** get the reflected vector
*/

t_ray	get_reflect_ray(t_objects obj, t_ray ray, float d)
{
	t_ray		reflect;

	if (obj.circle == 1)
		reflect = rf_sphere(obj, ray, d);
	else if (obj.cone == 1)
		reflect = rf_cone(obj, ray, d);
	else if (obj.cylinder == 1)
		reflect = rf_cylinder(obj, ray, d);
	else
		reflect = rf_plane(obj, ray, d);
	return (reflect);
}

/*
 ** reflection ray for sphere
*/

t_ray	rf_sphere(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	t_vector	n;
	float		c1;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 0.995));
	n = calc_unit_v(calc_p_to_v(obj.c, rf.sc));
	c1 = -calc_dp(n, calc_unit_v(ray.v));
	rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, (2 * c1)));
	return (rf);
}

/*
 ** reflection ray for cone
*/

t_ray	rf_cone(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	float		di;
	t_vector	n;
	float		c1;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 0.995));
	di = pow(calc_p_dist(rf.sc, obj.c), 2) / calc_dp(calc_p_to_v(obj.c,
				rf.sc), calc_unit_v(obj.dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di),
				rf.sc));
	c1 = -calc_dp(n, calc_unit_v(ray.v));
	rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, (2 * c1)));
	return (rf);
}

/*
 ** reflection ray for cylinder
*/

t_ray	rf_cylinder(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	float		di;
	t_vector	n;
	float		c1;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 0.995));
	di = calc_dp(calc_p_to_v(obj.c, rf.sc), calc_unit_v(obj.dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di),
				rf.sc));
	c1 = -calc_dp(n, calc_unit_v(ray.v));
	rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, (2 * c1)));
	return (rf);
}

/*
 ** reflection ray for plane
*/

t_ray	rf_plane(t_objects obj, t_ray ray, float d)
{
	t_ray		rf;
	t_vector	n;
	float		c1;

	rf.sc = calc_vect_to_point(ray.sc, ray.v, (d * 0.995));
	n = (t_vector){obj.dir.x, obj.dir.y, obj.dir.z, 0};
	if (calc_dp(n, ray.v) < 0)
		n = (t_vector){-obj.dir.x, -obj.dir.y, -obj.dir.z, 0};
	c1 = -calc_dp(n, calc_unit_v(ray.v));
	rf.v = calc_addition(calc_unit_v(ray.v), calc_multi(n, (2 * c1)));
	return (rf);
}

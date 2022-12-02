/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 10:01:51 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 15:42:49 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** find angles between vectors
*/

inline float	calc_vector_ang(t_vector a, t_vector b)
{
	return (acos((calc_dp(a, b)) / (calc_m(a) * calc_m(b))));
}

/*
 ** addition of two vectors
*/

t_vector		calc_addition(t_vector a, t_vector b)
{
	t_vector	ans;

	ans.x = a.x + b.x;
	ans.y = a.y + b.y;
	ans.z = a.z + b.z;
	ans.w = 0;
	return (ans);
}

/*
 ** cross product of 2 vectors
*/

t_vector		calc_cross_product(t_vector a, t_vector b)
{
	t_vector	ans;

	ans.x = a.y * b.z - a.z * b.y;
	ans.y = (a.x * b.z - a.z * b.x) * -1;
	ans.z = a.x * b.y - a.y * b.x;
	ans.w = 0;
	return (ans);
}

/*
 ** using points and vectors to get new points
*/

t_point			calc_vect_to_point(t_point p, t_vector v, float m)
{
	t_point	ans;
	float	d;

	d = calc_m(v);
	ans.x = p.x + v.x * (m / d);
	ans.y = p.y + v.y * (m / d);
	ans.z = p.z + v.z * (m / d);
	ans.w = 1;
	return (ans);
}

/*
 ** gets ray shot from camera
*/

t_ray			ray(t_obj obj, float x, float y)
{
	t_ray	ray;

	x = (-obj.camera.h_fov + x * obj.camera.xdeg) * obj.camera.ar;
	y = obj.camera.h_fov - y * obj.camera.ydeg;
	ray.v = calc_addition(calc_multi(obj.camera.view, cos(x)), calc_multi(
				obj.camera.hor, sin(x)));
	ray.v = calc_addition(calc_multi(ray.v, cos(y)), calc_multi(obj.camera.up,
					sin(y)));
	ray.sc = calc_vect_to_point(obj.camera.c, ray.v, obj.camera.dist);
	return (ray);
}

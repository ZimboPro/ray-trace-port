/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 09:12:48 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/08 13:53:26 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>
/*
 ** takes two points and changes it to a vector
*/

t_vector		calc_p_to_v(t_point a, t_point b)
{
	t_vector	ans;

	ans.x = b.x - a.x;
	ans.y = b.y - a.y;
	ans.z = b.z - a.z;
	ans.w = 0;
	return (ans);
}
/*
 ** takes two points and changes it to a vector
*/

t_vector		calc_p_to_vec(t_point a, Vec3 b)
{
	t_vector	ans;

	ans.x = b.x - a.x;
	ans.y = b.y - a.y;
	ans.z = b.z - a.z;
	ans.w = 0;
	return (ans);
}

/*
 ** returns distance between to points
*/

inline float	calc_p_dist(t_point a, t_point b)
{
	return (calc_m(calc_p_to_v(a, b)));
}

/*
 ** returns distance between to points
*/

inline float	calc_p_dist_vec(t_point a, Vec3 b)
{
	return (calc_m(calc_p_to_vec(a, b)));
}

/*
 ** returns the unit vector of a given vector
*/

t_vector		calc_unit_v(t_vector v)
{
	t_vector	ans;
	float		d;

	d = calc_m(v);
	ans.x = v.x / d;
	ans.y = v.y / d;
	ans.z = v.z / d;
	ans.w = 0;
	return (ans);
}

t_vector		calc_normal(t_vector v, t_point a, t_point b)
{
	t_vector	ab;
	float		ang;
	float		t;
	t_point		p;

	ab = calc_p_to_v(a, b);
	t = calc_m(ab);
	ang = calc_vector_ang(v, ab);
	t = t * cos(ang);
	p = calc_vect_to_point(a, v, t);
	return (calc_p_to_v(p, b));
}

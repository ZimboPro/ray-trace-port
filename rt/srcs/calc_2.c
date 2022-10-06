/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 08:51:57 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 08:52:07 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** rotate about x
*/

t_vector	rot_x(t_vector v, float r)
{
	float		y;
	float		z;
	t_vector	ans;

	y = v.y;
	z = v.z;
	ans = v;
	ans.y = y * cos(r) - z * sin(r);
	ans.z = y * sin(r) + z * cos(r);
	return (ans);
}

/*
 ** rotate about y
*/

t_vector	rot_y(t_vector v, float r)
{
	float		x;
	float		z;
	t_vector	ans;

	x = v.x;
	z = v.z;
	ans = v;
	ans.x = x * cos(r) + z * sin(r);
	ans.z = -x * sin(r) + z * cos(r);
	return (ans);
}

/*
 ** multiplies each component of vector by a value
*/

t_vector	calc_multi(t_vector a, float d)
{
	t_vector	ans;

	ans.x = a.x * d;
	ans.y = a.y * d;
	ans.z = a.z * d;
	ans.w = a.w;
	return (ans);
}

/*
 ** multiplies each component of vector by a value
*/

Vec3	calc_multi_vec(Vec3 a, float d)
{
	Vec3	ans;

	ans.x = a.x * d;
	ans.y = a.y * d;
	ans.z = a.z * d;
	return (ans);
}

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

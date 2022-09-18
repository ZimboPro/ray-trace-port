/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:42:29 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:42:36 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** checks to see if ray intersects and then calculates distance if it does
*/

static void		int_cylinder(float *d, t_quad cyl)
{
	cyl.t1 = (-cyl.b + sqrt(cyl.c)) / (2 * cyl.a);
	cyl.t2 = (-cyl.b - sqrt(cyl.c)) / (2 * cyl.a);
	if (cyl.t1 >= 0)
		*d = cyl.t1;
	if (cyl.t2 >= 0 && (cyl.t2 < cyl.t1 || *d == -1))
		*d = cyl.t2;
}

/*
 ** transforms the points and vectors before checking for intersections
*/

void			int_cyl(t_objects obj, float *d, t_ray ray)
{
	t_quad		cyl;
	float		dv;
	t_vector	co;
	float		cov;

	cyl.t1 = 0;
	cyl.t2 = 0;
	dv = calc_dp(calc_unit_v(obj.dir), calc_unit_v(ray.v));
	co = calc_p_to_v(obj.c, ray.sc);
	cov = calc_dp(co, calc_unit_v(obj.dir));
	cyl.a = (1 - dv * dv);
	cyl.b = 2 * calc_dp(co, calc_unit_v(ray.v)) - 2 * dv * cov;
	cyl.c = calc_dp(co, co) - cov * cov - obj.rad * obj.rad;
	cyl.c = (cyl.b * cyl.b) - (4 * cyl.a * cyl.c);
	if (cyl.c > 0)
		int_cylinder(d, cyl);
}

/*
 ** creates the transforamtion matrix
*/

float			**transf(t_vector cyl)
{
	float		z;
	float		y;
	t_vector	temp;
	t_vector	p;
	float		**rot;

	p = (t_vector){1, 0, 0, 1};
	temp = (t_vector){cyl.x, cyl.y, 0, 1};
	z = calc_vector_ang(p, temp);
	if (temp.y < 0)
		z = -z;
	p = (t_vector){0, 0, 1, 1};
	temp = (t_vector){cyl.x, 0, cyl.z, 1};
	y = calc_vector_ang(p, temp);
	if (temp.x < 0)
		y = -y;
	rot = rotation(0, y, z);
	return (rot);
}

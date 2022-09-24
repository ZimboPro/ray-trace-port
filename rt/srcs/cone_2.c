/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:39:50 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:39:57 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** if ray intersects then finds the closest distance
*/

static void		int_c(float *d, t_quad cone, t_objects obj, t_ray ray)
{
	t_vector	cp;

	cone.t1 = ((-cone.b + sqrt(cone.c)) / (2 * cone.a));
	cone.t2 = ((-cone.b - sqrt(cone.c)) / (2 * cone.a));
	if (cone.t1 >= 0)
		*d = cone.t1;
	if (cone.t2 >= 0 && (cone.t2 < cone.t1 || *d == -1))
		*d = cone.t2;
	if (*d != -1)
	{
		cp = calc_p_to_v(obj.c, calc_vect_to_point(ray.sc, ray.v, *d));
		if (calc_dp(cp, obj.dir) < 0)
			*d = -1;
	}
}

/*
 ** checks to see if ray intersects
*/

void			int_cone(t_objects obj, float *d, t_ray ray)
{
	float		ang;
	float		dv;
	t_vector	co;
	t_quad		cone;
	float		cov;

	cone.t1 = 0;
	cone.t2 = 0;
	ang = pow(cos(atan(obj.rad / obj.h)), 2);
	dv = calc_dp(calc_unit_v(ray.v), calc_unit_v(obj.dir));
	co = calc_p_to_v(obj.c, ray.sc);
	cov = calc_dp(calc_unit_v(obj.dir), co);
	cone.a = dv * dv - ang;
	cone.b = 2 * (dv * cov - calc_dp(calc_unit_v(ray.v), co) * ang);
	cone.c = cov * cov - calc_dp(co, co) * ang;
	cone.c = (cone.b * cone.b) - (4 * cone.a * cone.c);
	if (cone.c >= 0)
		int_c(d, cone, obj, ray);
}

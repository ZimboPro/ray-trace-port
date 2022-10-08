/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:45:59 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:46:05 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** finds closest point
*/
static void	int_circ(float *d, t_quad ci)
{
	ci.t1 = (-ci.b + sqrt(ci.c)) / (2 * ci.a);
	ci.t2 = (-ci.b - sqrt(ci.c)) / (2 * ci.a);
	if (ci.t1 > 0 && ci.t2 > 0)
	{
		if (ci.t1 <= ci.t2)
			*d = ci.t1;
		else
			*d = ci.t2;
	}
	else if (ci.t1 > 0)
		*d = ci.t1;
	else if (ci.t2 > 0)
		*d = ci.t2;
}

/*
 ** checks to see if ray intersects and and finds the distance if it does
*/
void		int_circle(t_objects circ, float *d, t_ray ray)
{
	t_quad		ci;
	t_vector	co;

	ci.a = 0;
	ci.b = 0;
	ci.c = 0;
	ci.t1 = 0;
	ci.t2 = 0;
	co = calc_p_to_v(circ.c, ray.sc);
	ci.a = 1;
	ci.b = 2 * calc_dp(calc_unit_v(ray.v), co);
	ci.c = calc_dp(co, co) - (circ.rad * circ.rad);
	ci.c = (ci.b * ci.b) - (4 * ci.a * ci.c);
	if (ci.c >= 0)
		int_circ(d, ci);
}

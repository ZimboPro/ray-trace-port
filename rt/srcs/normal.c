/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:00:00 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/13 12:53:46 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	cyl_norm(t_objects obj, float d, t_ray ray)
{
	t_vector	n;
	t_point		p;
	float		di;

	p = calc_vect_to_point(ray.sc, ray.v, d);
	di = calc_dp(calc_p_to_v(obj.c, p), calc_unit_v(obj.dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di), p));
	return (n);
}

t_vector	cone_norm(t_objects obj, float d, t_ray ray)
{
	t_vector	n;
	t_point		p;
	float		di;

	p = calc_vect_to_point(ray.sc, ray.v, d);
	di = pow(calc_p_dist(p, obj.c), 2) / calc_dp(calc_p_to_v(obj.c, p),
			calc_unit_v(obj.dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.c, obj.dir, di), p));
	return (n);
}

t_vector	normal(t_objects obj, float d, t_ray ray)
{
	t_vector	n;

	if (obj.cylinder == 1)
		n = cyl_norm(obj, d, ray);
	else
		n = cone_norm(obj, d, ray);
	return (n);
}

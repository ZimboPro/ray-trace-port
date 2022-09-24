/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:19:14 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:19:27 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** sphere color and shading
*/

void			cartoon_circle(t_obj obj, t_color *col, int i, t_ray rv)
{
	t_point		p;
	t_objects	circ;
	t_vector	n;

	circ = obj.objects[i];
	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 1.05));
	if (calc_p_dist(p, circ.c) > circ.rad)
		*col = (t_color){0, 0, 0};
	else
	{
		p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
		n = calc_unit_v(calc_p_to_v(circ.c, p));
		*col = cartoon_color(obj, (t_ray){p, n}, i);
	}
}

/*
 ** cylinder color and shading
*/

void			cartoon_cylinder(t_obj obj, t_color *col, int i, t_ray rv)
{
	t_point		p;
	float		di;
	t_vector	n;
	t_point		p1;

	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 1.05));
	di = calc_dp(calc_p_to_v(obj.objects[i].c, p),
			calc_unit_v(obj.objects[i].dir));
	p1 = calc_vect_to_point(obj.objects[i].c, obj.objects[i].dir, di);
	if (calc_p_dist(p, p1) > obj.objects[i].rad)
		*col = (t_color){0, 0, 0};
	else
	{
		p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
		di = calc_dp(calc_p_to_v(obj.objects[i].c, p),
				calc_unit_v(obj.objects[i].dir));
		n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.objects[i].c,
						obj.objects[i].dir, di), p));
		*col = cartoon_color(obj, (t_ray){p, n}, i);
	}
}

/*
 ** cone color and shading
*/

void			cartoon_cone(t_obj obj, t_color *col, int i, t_ray rv)
{
	t_point		p;
	t_vector	n;
	float		di;

	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 1.05));
	di = -1;
	int_cone(obj.objects[i], &di, (t_ray){p, rv.v});
	if (di == -1)
		*col = (t_color){0, 0, 0};
	else
	{
		p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
		di = pow(calc_p_dist(p, obj.objects[i].c), 2) / calc_dp(
				calc_p_to_v(obj.objects[i].c, p),
				calc_unit_v(obj.objects[i].dir));
		n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.objects[i].c,
					obj.objects[i].dir, di), p));
		*col = cartoon_color(obj, (t_ray){p, n}, i);
	}
}

/*
 ** sphere plane and shading
*/

void			cartoon_plane(t_obj obj, t_color *col, int i, t_ray rv)
{
	t_point		p;
	t_objects	plane;
	t_vector	n;

	plane = obj.objects[i];
	n = (t_vector){plane.dir.x, plane.dir.y, plane.dir.z, 0 };
	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
	*col = cartoon_color(obj, (t_ray){p, n}, i);
}

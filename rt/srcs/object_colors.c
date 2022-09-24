/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 08:45:41 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/27 16:30:33 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** finds color with lights ie multi-lights and checks if light source is
 ** closer than object if intersection
*/

static t_color	light_color(t_obj obj, t_ray n, int i)
{
	t_cart	h;

	h.k = 0;
	h.j = 0;
	while (h.k < obj.light)
	{
		h.tmp = 0;
		h.l = calc_unit_v(calc_p_to_v(n.sc, obj.lights[h.k].c));
		if (obj.objects[i].plane == 0 && (h.tmp = calc_dp(h.l, n.v)) < 0)
			h.tmp /= 6;
		else if (intersection(obj, &(obj.d), h.l, n.sc) != -1 &&
				calc_p_dist(n.sc, obj.lights[h.k].c) > obj.d)
			h.tmp = 0;
		else if (obj.objects[i].plane == 1)
			h.tmp = 1;
		h.j += h.tmp;
		h.k++;
	}
	h.j /= ((float)h.k);
	h.co = (t_color){obj.objects[i].col.r * (AMB + (1 - AMB) * h.j),
			obj.objects[i].col.g * (AMB + (1 - AMB) * h.j),
			obj.objects[i].col.b * (AMB + (1 - AMB) * h.j)};
	return (h.co);
}

/*
 ** sphere color and shading
*/

t_color			color_circle(t_obj obj, int i, t_ray rv)
{
	t_point		p;
	t_objects	circ;
	t_vector	n;

	circ = obj.objects[i];
	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
	n = calc_unit_v(calc_p_to_v(circ.c, p));
	obj.objects[i] = texture(obj.objects[i], rv, n);
	if (obj.objects[i].reflect > 0)
		return (blinn_phong(obj, (t_ray){p, n}, i, rv.v));
	return (light_color(obj, (t_ray){p, n}, i));
}

/*
 ** cylinder color and shading
*/

t_color			color_cylinder(t_obj obj, int i, t_ray rv)
{
	t_point		p;
	float		di;
	t_vector	n;

	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
	di = calc_dp(calc_p_to_v(obj.objects[i].c, p),
			calc_unit_v(obj.objects[i].dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.objects[i].c,
			obj.objects[i].dir, di), p));
	obj.objects[i] = texture(obj.objects[i], rv, n);
	if (obj.objects[i].reflect > 0)
		return (blinn_phong(obj, (t_ray){p, n}, i, rv.v));
	return (light_color(obj, (t_ray){p, n}, i));
}

/*
 ** cone color and shading
*/

t_color			color_cone(t_obj obj, int i, t_ray rv)
{
	t_point		p;
	t_vector	n;
	float		di;

	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
	di = pow(calc_p_dist(p, obj.objects[i].c), 2) / calc_dp(
			calc_p_to_v(obj.objects[i].c, p), calc_unit_v(obj.objects[i].dir));
	n = calc_unit_v(calc_p_to_v(calc_vect_to_point(obj.objects[i].c,
					obj.objects[i].dir, di), p));
	obj.objects[i] = texture(obj.objects[i], rv, n);
	if (obj.objects[i].reflect > 0)
		return (blinn_phong(obj, (t_ray){p, n}, i, rv.v));
	return (light_color(obj, (t_ray){p, n}, i));
}

/*
 ** sphere plane and shading
*/

t_color			color_plane(t_obj obj, int i, t_ray rv)
{
	t_point		p;
	t_objects	plane;
	t_vector	n;
	t_vector	l;

	plane = obj.objects[i];
	n = (t_vector){plane.dir.x, plane.dir.y, plane.dir.z, 0 };
	p = calc_vect_to_point(rv.sc, rv.v, (obj.d * 0.995));
	l = calc_unit_v(calc_p_to_v(p, obj.lights[0].c));
	obj.objects[i] = texture(obj.objects[i], rv, n);
	if (calc_dp(l, p) < 0)
		n = (t_vector){-plane.dir.x, -plane.dir.y, -plane.dir.z, 0 };
	if (obj.objects[i].reflect > 0)
		return (blinn_phong(obj, (t_ray){p, n}, i, rv.v));
	return (light_color(obj, (t_ray){p, n}, i));
}

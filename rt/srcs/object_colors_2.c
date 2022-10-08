/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objecSDL_Colors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:41:29 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 10:41:38 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** blinn-phong ligthing
*/
float			blinn_helper(t_obj obj, t_ray n, t_cart h)
{
	if (obj.objects[h.i].type != Plane && (h.tmp = calc_dp(h.l, n.v)) < 0.0f)
		h.tmp = 0.0f;
	else if (intersection(obj, &(obj.d), calc_unit_v(calc_p_to_vec(n.sc,
		obj.lights[h.k].c)), n.sc) != -1
		&& calc_p_dist_vec(n.sc, obj.lights[h.k].c) > obj.d)
		h.tmp = 0.0f;
	else if (obj.objects[h.i].type == Plane
		&& (h.tmp = calc_dp(h.l, n.v)) < 0.0f)
		h.tmp = -h.tmp;
	h.tmp = pow(obj.objects[h.i].reflect, 2) * pow(h.tmp, 1000);
	return (h.tmp);
}

SDL_Color			blinn_phong(t_obj obj, t_ray n, int i, t_vector v)
{
	t_cart	h;

	h.k = 0;
	h.j = 0;
	h.co = obj.objects[i].col;
	while (h.k < obj.light)
	{
		h.tmp = 1;
		h.l = calc_unit_v(calc_p_to_vec(n.sc, obj.lights[h.k].c));
		h.l = calc_addition(h.l, calc_multi(calc_unit_v(v), -1));
		if (calc_m(h.l) != 0.0f)
		{
			h.l = calc_unit_v(h.l);
			h.tmp = blinn_helper(obj, n, h);
		}
		h.j += h.tmp;
		h.k++;
	}
	h.j /= ((float)h.k);
	h.co.r = ((h.co.r += (int)((float)h.co.r * h.j)) > 255) ? 255 : h.co.r;
	h.co.g = ((h.co.g += (int)((float)h.co.g * h.j)) > 255) ? 255 : h.co.g;
	h.co.b = ((h.co.b += (int)((float)h.co.b * h.j)) > 255) ? 255 : h.co.b;
	return (h.co);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:06 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/13 07:09:54 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>

/*
 ** finds color with lights ie multi-lights and checks if light source is
 ** closer than object if intersection
*/

static SDL_Color	cartoon_help(SDL_Color col, float j)
{
	return dim_color(&col, (AMB + (1 - AMB) * j));
}

SDL_Color			cartoon_color(t_obj obj, t_ray n, int i)
{
	t_cart c;

	c.k = 0;
	c.j = 0;
	while (c.k < obj.light)
	{
		c.tmp = 0;
		c.l = calc_unit_v(calc_p_to_vec(n.sc, obj.lights[c.k].c));
		if (obj.objects[i].type != Plane && (c.tmp = calc_dp(c.l, n.v)) < 0)
			c.tmp = 0;
		else if (intersection(obj, &(obj.d), c.l, n.sc) != -1 &&
				calc_p_dist_vec(n.sc, obj.lights[c.k].c) > obj.d)
			c.tmp = 0;
		else if (obj.objects[i].type == Plane)
			c.tmp = 1;
		else if (c.tmp < 0.5)
			c.tmp = 0.5;
		else
			c.tmp = 1;
		c.j += c.tmp;
		c.k++;
	}
	c.j /= ((float)c.k);
	c.co = cartoon_help(obj.objects[i].col, c.j);
	return (c.co);
}

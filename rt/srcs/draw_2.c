/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:53:56 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:54:05 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>


/*
 ** does the ray tracing and gets the color with reflection and
 ** refration if applicable
*/
SDL_Color			trace_ray(t_obj obj, t_ray ray, int depth, SDL_Renderer *ren)
{
	t_traceh	k;

	if (depth < DEPTH && (k.i =
		intersection(obj, &(obj.d), ray.v, ray.sc)) != -1)
	{
		k.p_c = get_color(obj, ren, k.i, ray);
		k.f = obj.objects[k.i].reflect;
		if (obj.objects[k.i].reflect > 0 && obj.objects[k.i].refract == 1000293)
		{
			k.temp = get_reflect_ray(obj.objects[k.i], ray, obj.d);
			k.rlc =
			color_adjust(trace_ray(obj, k.temp, depth + 1, ren), k.f);
			k.p_c = mix_color(k.rlc, k.p_c);
		}
		if (obj.objects[k.i].refract != 1000293)
		{
			obj.i = k.i;
			k.rlc = fresnel_effect(obj, ray, depth, ren);
			k.p_c = (SDL_Color){k.rlc.r * k.f + k.p_c.r * (1 - k.f), k.rlc.g * k.f
				+ k.p_c.g * (1 - k.f), k.rlc.b * k.f + k.p_c.b * (1 - k.f), 255};
		}
		return (k.p_c);
	}
	return (obj.camera.bg);
}

/*
 ** gets object color and shading
*/
SDL_Color			get_color(t_obj obj, SDL_Renderer *ren, int i, t_ray ry)
{
	SDL_Color	col;

	miss(ren);
	if (obj.objects[i].type == Circle)
		col = color_circle(obj, i, ry);
	else if (obj.objects[i].type == Cylinder)
		col = color_cylinder(obj, i, ry);
	else if (obj.objects[i].type == Cone)
		col = color_cone(obj, i, ry);
	else
		col = color_plane(obj, i, ry);
	return (col);
}

void			miss(SDL_Renderer *ren)
{
	SDL_RenderIsClipEnabled(ren);
}

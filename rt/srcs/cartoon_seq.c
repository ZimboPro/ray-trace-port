/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_seq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:41:32 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/16 13:59:41 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>
/*
 ** fresnel equation and effect for cartoon mode
*/
static SDL_Color	fresnel_effect_cart(t_obj obj, t_ray ray, int depth,
		SDL_Renderer *ren)
{
	t_ray		n;
	float		f;
	SDL_Color		rfl;
	SDL_Color		rfr;
	int			i;

	i = obj.i;
	n.sc = calc_vect_to_point(ray.sc, ray.v, obj.d);
	n.v = calc_unit_v(calc_p_to_v(obj.objects[i].c, n.sc));
	f = fresnel(1.000293, obj.objects[i].refract, n.v, ray.v);
	if (f == 1)
		return (trace_ray_cart(obj, ray, depth + 1, ren));
	else
	{
		f = f * obj.objects[i].reflect;
		rfl = trace_ray_cart(obj, get_reflect_ray(obj.objects[i], ray, obj.d),
				depth + 1, ren);
		rfr = trace_ray(obj, get_refract_ray(obj.objects[i], ray, obj.d),
				depth + 1, ren);
		rfr = (SDL_Color){rfl.r * f + rfr.r * (1 - f), rfl.g
			* f + rfr.g * (1 - f), rfl.b * f + rfr.b * (1 - f), 255};
	}
	return (rfr);
}

/*
 ** does the ray tracing and gets the color with reflection and
 ** refration if applicable for cartoon mode
*/
SDL_Color			trace_ray_cart(t_obj obj, t_ray ray, int depth,
	SDL_Renderer *ren)
{
	t_colh	h;

	if (depth < DEPTH && (obj.i =
		intersection(obj, &(obj.d), ray.v, ray.sc)) != -1)
	{
		h.p_c = get_cartoon_color(obj, ren, obj.i, ray);
		h.f = OBJI.reflect;
		if (OBJI.reflect > 0 && OBJI.refract == 1000293)
		{
			h.temp = get_reflect_ray(OBJI, ray, obj.d);
			h.rlc =
			color_adjust(trace_ray_cart(obj, h.temp, depth + 1, ren), h.f);
			h.p_c = (SDL_Color){(h.rlc.r + h.p_c.r) >> 1, (h.rlc.g + h.p_c.g)
				>> 1, (h.rlc.b + h.p_c.b) >> 1, 255};
		}
		if (OBJI.refract != 1000293)
		{
			h.rlc = fresnel_effect_cart(obj, ray, depth, ren);
			h.p_c = (SDL_Color){h.rlc.r * h.f + h.p_c.r * (1 - h.f), h.rlc.g
			* h.f + h.p_c.g * (1 - h.f), h.rlc.b * h.f + h.p_c.b * (1 - h.f), 255};
		}
		return (h.p_c);
	}
	return (obj.camera.bg);
}

/*
 ** creates threads
*/
void			cartoon_draw(t_obj *obj, SDL_Renderer *ren)
{
	pthread_t	pthid[4];
	t_temp		temp[4];
	// size_t		d;
	int			i;

	i = -1;
	// d = (obj->camera.width * obj->camera.height) >> 2;
	while (++i < 4)
	{
		temp[i] = thr_init(obj, ren, i);
		pthread_create(&pthid[i], NULL, cartoon_threading, &temp[i]);
	}
	if (obj->first == 0)
	{
		progress(obj, ren);
		obj->first = 1;
	}
	i = -1;
	while (++i < 4)
	{
		pthread_join(pthid[i], NULL);
		ft_point(temp[i].img, temp[i].len, ren);
		free(temp[i].img);
	}
	interface(ren);
}

/*
 ** gets object color and cartoon shading
*/
SDL_Color			get_cartoon_color(t_obj obj, SDL_Renderer *ren, int i, t_ray ry)
{
	SDL_Color	col;

	col = (SDL_Color){0, 0, 0, 255};
	miss(ren);
	if (obj.objects[i].type == Circle)
		cartoon_circle(obj, &col, i, ry);
	else if (obj.objects[i].type == Cylinder)
		cartoon_cylinder(obj, &col, i, ry);
	else if (obj.objects[i].type == Cone)
		cartoon_cone(obj, &col, i, ry);
	else
		cartoon_plane(obj, &col, i, ry);
	return (col);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 15:14:50 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/16 14:20:29 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** draws pixel point
*/
void			ft_point(t_pix_colors *arr, size_t len, SDL_Renderer *ren)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		SDL_SetRenderDrawColor(ren, arr[i].c.r, arr[i].c.g, arr[i].c.b, 0);
		SDL_RenderDrawPoint(ren, arr[i].p.x, arr[i].p.y);
		i++;
	}
}

/*
 ** goes thorugh each pixel and finds what color to draw
*/
void			ft_draw(t_obj *obj, SDL_Renderer *ren)
{
	pthread_t	pthid[4];
	t_temp		temp[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		temp[i] = thr_init(obj, ren, i);
		pthread_create(&pthid[i], NULL, threading, &temp[i]);
		i++;
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
 ** fresnel equation, the ratio of refraction and reflaction at a point
*/
float			fresnel(float n1, int n2, t_vector n, t_vector v)
{
	float	r0;
	float	c1;
	float	x;
	float	ret;
	float	n2t;

	n2t = ((float)n2) / 1000000;
	r0 = (n1 - n2t) / (n1 + n2t);
	r0 *= r0;
	c1 = -calc_dp(n, v);
	if (n1 > n2t)
	{
		ret = n1 / n2t;
		x = ret * ret * (1 - c1 * c1);
		if (x > 1)
			return (1);
		c1 = sqrt(1 - x);
	}
	x = 1 - c1;
	ret = r0 + (1 - r0) * x * x * x * x * x;
	return (ret);
}

/*
 ** fresnel equation and effect
*/
SDL_Color			fresnel_effect(t_obj obj, t_ray ray, int depth,
		SDL_Renderer *ren)
{
	t_ray		n;
	float		f;
	SDL_Color		rfl;
	SDL_Color		rfr;

	n.sc = calc_vect_to_point(ray.sc, ray.v, obj.d);
	if (OBJI.type == Cylinder || OBJI.type == Cone)
		n.v = normal(OBJI, obj.d, ray);
	else
		n.v = calc_unit_v(calc_p_to_v(OBJI.c, n.sc));
	f = fresnel(1.000293, OBJI.refract, n.v, ray.v);
	if (f == 1)
		return (trace_ray(obj, ray, depth + 1, ren));
	else
	{
		f = f * OBJI.reflect;
		rfl = trace_ray(obj, get_reflect_ray(OBJI, ray, obj.d),
				depth + 1, ren);
		rfr = trace_ray(obj, get_refract_ray(OBJI, ray, obj.d),
				depth + 1, ren);
		rfr = (SDL_Color){rfl.r * f + rfr.r * (1 - f), rfl.g * f + rfr.g *
			(1 - f), rfl.b * f + rfr.b * (1 - f), 255};
	}
	return (rfr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:10:53 by syoung            #+#    #+#             */
/*   Updated: 2017/09/21 09:10:54 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>
/*
 ** anti-aliasing
*/

SDL_Color		aa_col(t_obj obj, int x, int y, SDL_Renderer *ren)
{
	t_ray	rays[4];
	SDL_Color	p;
	SDL_Color	t;
	int		i;

	i = 0;
	rays[0] = ray(obj, (float)x - 0.25, (float)y - 0.25);
	rays[1] = ray(obj, (float)x + 0.25, (float)y - 0.25);
	rays[2] = ray(obj, (float)x - 0.25, (float)y + 0.25);
	rays[3] = ray(obj, (float)x + 0.25, (float)y + 0.25);
	p = (SDL_Color){0, 0, 0, 255};
	while (i < 4)
	{
		t = trace_ray(obj, rays[i], 0, ren);
		if (i == 0) {
			p = t;
		} else {
			p = mix_color(p, t);
		}
		i++;
	}
	return (p);
}

/*
 ** cartoon anti_aliasing ray trace with threading
*/

void		cartoon_draw_aa(t_obj *obj, SDL_Renderer *ren)
{
	pthread_t	pthid[4];
	t_temp		temp[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		temp[i] = thr_init(obj, ren, i);
		pthread_create(&pthid[i], NULL, threading_cart_aa, &temp[i]);
		i++;
	}
	if (obj->first == 0)
	{
		progress(obj, ren);
		obj->first = 1;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(pthid[i], NULL);
		ft_point(temp[i].img, temp[i].len, ren);
		free(temp[i].img);
		i++;
	}
	interface(ren);
}

/*
 ** anti-aliasing thread
*/

void		*threading_cart_aa(void *arg)
{
	t_temp	*t;
	int		x;
	int		y;
	SDL_Color	p;

	t = (t_temp *)arg;
	y = t->y_b;
	while (y < t->y_e && t->len < t->size)
	{
		x = t->x_b;
		while (x < t->x_e && t->len < t->size)
		{
			p = aa_cartoon_col(*t->obj, x, y, t->ren);
			t->img[t->len] = (t_pix_colors){p, (t_pixel){x, y}};
			t->len += 1;
			x++;
		}
		if (t->obj->first == 0 && ((y + 1) % (int)((t->obj->camera.height)
						/ 25)) == 0)
			progress_update(t->obj);
		y++;
	}
	pthread_exit(NULL);
}

/*
 ** anti-aliasing
*/

SDL_Color		aa_cartoon_col(t_obj obj, int x, int y, SDL_Renderer *ren)
{
	t_ray	rays[4];
	SDL_Color	p;
	SDL_Color	t;
	int		i;

	i = 0;
	rays[0] = ray(obj, (float)x - 0.25, (float)y - 0.25);
	rays[1] = ray(obj, (float)x + 0.25, (float)y - 0.25);
	rays[2] = ray(obj, (float)x - 0.25, (float)y + 0.25);
	rays[3] = ray(obj, (float)x + 0.25, (float)y + 0.25);
	p = (SDL_Color){0, 0, 0, 255};
	while (i < 4)
	{
		t = trace_ray_cart(obj, rays[i], 0, ren);
		if (i == 0) {
			p = t;
		} else {
			p = mix_color(p, t);
		}
		i++;
	}
	return (p);
}

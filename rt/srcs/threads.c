/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 06:39:48 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/16 14:16:20 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*threading(void *arg)
{
	t_temp	*t;
	int		y;
	int		x;
	t_ray	rv;
	t_color	p;

	t = (t_temp *)arg;
	y = t->y_b;
	while (y < t->y_e && t->len < t->size)
	{
		x = t->x_b;
		while (x < t->x_e && t->len < t->size)
		{
			rv = ray(*t->obj, x, y);
			p = trace_ray(*t->obj, rv, 0, t->ren);
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
 ** cartoon thread ray trace
*/

void	*cartoon_threading(void *arg)
{
	t_temp	*t;
	int		y;
	int		x;
	t_ray	rv;
	t_color	p;

	t = (t_temp *)arg;
	y = t->y_b;
	while (y < t->y_e && t->len < t->size)
	{
		x = t->x_b;
		while (x < t->x_e && t->len < t->size)
		{
			rv = ray(*t->obj, x, y);
			p = trace_ray_cart(*t->obj, rv, 0, t->ren);
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
 ** initialises the data for threading
*/

t_temp	thr_init(t_obj *obj, SDL_Renderer *ren, int i)
{
	t_temp			t;
	static size_t	d = 0;

	if (d == 0)
		d = (obj->camera.width * obj->camera.height) >> 2;
	t.obj = obj;
	t.ren = ren;
	t.x_b = (obj->camera.width >> 2) * i;
	t.x_e = (obj->camera.width >> 2) * (i + 1);
	t.y_b = 0;
	t.y_e = obj->camera.height;
	t.img = (t_pix_colors *)malloc(sizeof(t_pix_colors) * d);
	t.size = d;
	t.len = 0;
	return (t);
}

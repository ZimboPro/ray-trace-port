/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:25:30 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/18 07:32:26 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** handles events and commands
*/

static int	ft_events_aa(SDL_Window *win, t_obj *obj)
{
	SDL_Renderer	*ren;
	int				loop;
	int				draw;

	ren = SDL_CreateRenderer(win, -1, 0);
	loop = 1;
	draw = 0;
	while (loop)
	{
		if (draw == 0)
		{
			if (obj->camera.mode == 0)
				ft_draw_aa(obj, ren);
			else
				cartoon_draw_aa(obj, ren);
			draw = 1;
		}
		ft_evn(&loop, obj, &draw);
	}
	interface(ren);
	return (0);
}

/*
 ** anti-aliasing raytrace
*/

static void	raytrace_aa(t_obj *obj)
{
	SDL_Window	*win;

	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			obj->camera.width, obj->camera.height, 0);
	while (ft_events_aa(win, obj))
		;
	SDL_DestroyWindow(win);
}

/*
 ** main sequence of events for anti-aliasing
*/

void		aa_seq(char *str)
{
	char	**s;
	t_obj	obj;

	s = ft_read(str);
	if (s != NULL)
	{
		if (map_check(s) == 1)
		{
			obj = objects(s);
			obj_assign(&obj, s);
			ft_strarrdel(s);
			raytrace_aa(&obj);
			free(obj.objects);
			obj.objects = NULL;
			free(obj.lights);
			obj.lights = NULL;
		}
	}
}

/*
 ** normal anti_aliasing ray trace with threading
*/

void		ft_draw_aa(t_obj *obj, SDL_Renderer *ren)
{
	pthread_t	pthid[4];
	t_temp		temp[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		temp[i] = thr_init(obj, ren, i);
		pthread_create(&pthid[i], NULL, threading_aa, &temp[i]);
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

void		*threading_aa(void *arg)
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
			p = aa_col(*t->obj, x, y, t->ren);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 15:50:41 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 15:53:40 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** update camera view
*/
void			update_pos(t_obj *obj, int *draw, int dir)
{
	t_point		p;

	if (dir == 0)
		p = calc_vect_to_point(obj->camera.c, obj->camera.view, DIST * DIST);
	else if (dir == 1)
		p = calc_vect_to_point(obj->camera.c, obj->camera.view, -(DIST * DIST));
	else if (dir == 2)
		p = calc_vect_to_point(obj->camera.c, obj->camera.hor, -DIST);
	else if (dir == 3)
		p = calc_vect_to_point(obj->camera.c, obj->camera.hor, DIST);
	else if (dir == 4)
		p = calc_vect_to_point(obj->camera.c, obj->camera.up, DIST);
	else
		p = calc_vect_to_point(obj->camera.c, obj->camera.up, -DIST);
	*draw = 0;
	obj->camera.c = p;
}

/*
 ** update camera view
*/
static t_vector	update_view_helper(t_obj *obj, int dir)
{
	t_vector temp;

	if (dir == 0)
	{
		temp = calc_addition(calc_multi(obj->camera.view, cos(ROTATE *
					(M_PI / 180))), calc_multi(obj->camera.up,
							sin(ROTATE * (M_PI / 180))));
		obj->camera.up = calc_addition(calc_multi(obj->camera.up, cos(ROTATE *
					(M_PI / 180))), calc_multi(obj->camera.view,
					-sin(ROTATE * (M_PI / 180))));
	}
	else
	{
		temp = calc_addition(calc_multi(obj->camera.view, cos(ROTATE *
						(M_PI / 180))), calc_multi(obj->camera.up,
							-sin(ROTATE * (M_PI / 180))));
		obj->camera.up = calc_addition(calc_multi(obj->camera.up, cos(ROTATE *
					(M_PI / 180))), calc_multi(obj->camera.view,
					sin(ROTATE * (M_PI / 180))));
	}
	return (temp);
}

void			update_view(t_obj *obj, int *draw, int dir)
{
	t_vector	temp;

	if (dir == 0 || dir == 1)
		temp = update_view_helper(obj, dir);
	if (dir == 2)
	{
		temp = calc_addition(calc_multi(obj->camera.view, cos(ROTATE *
						(M_PI / 180))), calc_multi(obj->camera.hor,
							-sin(ROTATE * (M_PI / 180))));
		obj->camera.hor = calc_addition(calc_multi(obj->camera.hor, cos(ROTATE *
					(M_PI / 180))), calc_multi(obj->camera.view,
					sin(ROTATE * (M_PI / 180))));
	}
	else
	{
		temp = calc_addition(calc_multi(obj->camera.view, cos(ROTATE *
						(M_PI / 180))), calc_multi(obj->camera.hor,
							sin(ROTATE * (M_PI / 180))));
		obj->camera.hor = calc_addition(calc_multi(obj->camera.hor, cos(ROTATE *
					(M_PI / 180))), calc_multi(obj->camera.view,
					-sin(ROTATE * (M_PI / 180))));
	}
	obj->camera.view = temp;
	*draw = 0;
}

/*
 ** event keys and their respective action
*/
void			ft_eventloop(SDL_Event event, int *loop, t_obj *obj, int *draw)
{
	if (event.type == SDL_QUIT)
		*loop = 0;
	else if (event.key.keysym.sym == SDLK_ESCAPE)
		*loop = 0;
	else if (event.key.keysym.sym == SDLK_w)
		update_view(obj, draw, 0);
	else if (event.key.keysym.sym == SDLK_s)
		update_view(obj, draw, 1);
	else if (event.key.keysym.sym == SDLK_a)
		update_view(obj, draw, 2);
	else if (event.key.keysym.sym == SDLK_d)
		update_view(obj, draw, 3);
	else if (event.key.keysym.sym == SDLK_UP)
		update_pos(obj, draw, 0);
	else if (event.key.keysym.sym == SDLK_DOWN)
		update_pos(obj, draw, 1);
	else if (event.key.keysym.sym == SDLK_LEFT)
		update_pos(obj, draw, 2);
	else if (event.key.keysym.sym == SDLK_RIGHT)
		update_pos(obj, draw, 3);
	else if (event.key.keysym.sym == SDLK_KP_PLUS)
		update_pos(obj, draw, 4);
	else if (event.key.keysym.sym == SDLK_KP_MINUS)
		update_pos(obj, draw, 5);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 15:56:19 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/18 07:12:05 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** increments the progress amount
*/
void			progress_update(t_obj *obj)
{
	obj->progress += 1;
}

/*
 ** draws an updates the progress bar
*/
static void		prog_help(t_prog *h, t_obj *obj, SDL_Renderer *ren)
{
	while (h->y < obj->camera.height)
	{
		h->x = 0;
		while (h->x < obj->camera.width)
		{
			if (h->x >= h->p_s && h->x <= h->p_e && h->y
				>= ((obj->camera.height >> 1) - (h->p_h >> 1)) && h->y
				<= ((obj->camera.height >> 1) + (h->p_h >> 1)))
			{
				if (h->x < ((h->p_e - h->p_s) / 100) * h->t + (h->p_s + 1))
					SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
				else
					SDL_SetRenderDrawColor(ren, 100, 0, 0, 0);
			}
			else
				SDL_SetRenderDrawColor(ren, 30, 30, 30, 0);
			SDL_RenderDrawPoint(ren, h->x, h->y);
			h->x++;
		}
		h->y++;
	}
}

void			progress(t_obj *obj, SDL_Renderer *ren)
{
	t_prog	h;

	h.y = 0;
	h.p_h = obj->camera.height / 10;
	h.p_s = obj->camera.width >> 2;
	h.p_e = (obj->camera.width >> 2) * 3;
	while (obj->progress <= 100)
	{
		h.t = obj->progress;
		ft_putnbr(h.t);
		ft_putendl("%");
		SDL_RenderClear(ren);
		prog_help(&h, obj, ren);
		interface(ren);
		if (h.t == 100)
			break ;
	}
	SDL_RenderClear(ren);
}

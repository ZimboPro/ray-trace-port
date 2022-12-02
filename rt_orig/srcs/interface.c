/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:05:01 by syoung            #+#    #+#             */
/*   Updated: 2017/09/12 08:58:20 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	interface(SDL_Renderer *ren)
{
	int x;
	int y;

	x = 40;
	y = 15;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	while (y <= 65)
	{
		SDL_RenderDrawPoint(ren, x, y);
		y++;
	}
	y -= 25;
	x = 14;
	while (++x < 65)
		SDL_RenderDrawPoint(ren, x, y);
	x = 15;
	y = 100;
	while (x < 65)
	{
		SDL_RenderDrawPoint(ren, x, y);
		x++;
	}
	SDL_RenderPresent(ren);
}

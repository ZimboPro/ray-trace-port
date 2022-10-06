/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:01:56 by syoung            #+#    #+#             */
/*   Updated: 2017/09/27 16:30:31 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objects			texture(t_objects object, t_ray rv, t_vector n)
{
	static SDL_Surface	*surf = NULL;
	static char			*tex = "default.bmp";

	if (object.circle && (ft_strcmp("NULL", object.texmap) != 0))
	{
		if (strcmp(tex, object.texmap) != 0)
		{
			tex = ft_strdup(object.texmap);
			surf = SDL_LoadBMP(tex);
		}
		object.col = tex_map(surf, n);
	}
	else if (object.pattern)
		pattern(object, n, rv);
	if (object.filter)
	{
		if (object.filter == 1)
			object.col = sepia(object.col);
	}
	return (object);
}

t_objects			pattern(t_objects object, t_vector n, t_ray rv)
{
	t_tex	t;
	SDL_Color	c;

	c = pattern_init(&t, n);
	if (object.pattern == 1)
		t.pattern = (modulo(t.s * t.scale_s) < 0.5);
	else if (object.pattern == 2)
		t.pattern = checker(t);
	else if (object.pattern == 3)
		c = marble(&t, n);
	if (t.pattern < 1)
		t.pattern = 20;
	else
		t.pattern = 1;
	c.r += t.pattern;
	c.g += t.pattern;
	c.b += t.pattern;
	if (object.pattern == 4)
	{
		c.g = perlin2d((int)fabs(rv.v.x * 1000),
			(int)fabs(rv.v.y * 1000), 0.1, 4) * 255;
		c.b = perlin2d((int)fabs(n.x * 5000),
			(int)fabs(n.y * 5000), 0.1, 4) * 255;
	}
	object.col = c;
	return (object);
}

static Uint32	get_pixel(SDL_Surface *surf, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surf->format->BytesPerPixel;
	p = (Uint8 *)surf->pixels + y * surf->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	return (*(Uint32 *)p);
}

SDL_Color			tex_map(SDL_Surface *surf, t_vector n)
{
	t_texmap t;

	t.red = 0;
	t.green = 0;
	t.blue = 0;
	t.alpha = 0;
	if (surf == NULL)
		return (t.col = (SDL_Color){t.blue, t.red, t.green, 255});
	SDL_LockSurface(surf);
	t.width = (int)surf->w;
	t.height = (int)surf->h;
	t.u = 0.5 + atan2f(n.z, n.x) / (TAU);
	t.v = 0.5 - asinf(n.y) / M_PI;
	t.width = (t.width - 1) * t.u;
	t.height = (t.width - 1) * t.v;
	t.pixelcol = get_pixel(surf, t.width, t.height);
	SDL_GetRGB(t.pixelcol, surf->format, &t.red, &t.green, &t.blue);
	t.col = (SDL_Color){t.red, t.green, t.blue, 255};
	SDL_UnlockSurface(surf);
	return (t.col);
}

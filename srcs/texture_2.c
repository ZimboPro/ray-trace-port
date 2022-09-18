/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:05:19 by syoung            #+#    #+#             */
/*   Updated: 2017/09/21 09:05:20 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			modulo(float f)
{
	return (f - floor(f));
}

float			checker(t_tex t)
{
	t.angle = 1.5708;
	t.s = t.tex_x * cos(t.angle) - t.tex_y * sin(t.angle);
	t.t = t.tex_y * cos(t.angle) + t.tex_x * sin(t.angle);
	t.pattern = (modulo(t.s * t.scale_s) < 0.5)
	^ (modulo(t.t * t.scale_t) < 0.5);
	return (t.pattern);
}

t_color			marble(t_tex *t, t_vector n)
{
	float	noise;
	t_color	c;

	c = (t_color){52, 67, 62};
	t->scale_s = 100;
	noise = perlin2d(t->scale_s * 0.5 * n.y, t->scale_t * 0.5 * n.x, 0.1, 4);
	t->angle = 0.523599;
	t->s = t->tex_x * cos(t->angle) - t->tex_y * sin(t->angle);
	t->pattern = (modulo(t->s * t->scale_s * noise) < 0.5);
	return (c);
}

t_color			pattern_init(t_tex *t, t_vector n)
{
	t_color c;

	t->scale_s = 10;
	t->scale_t = 10;
	t->angle = 0.523599;
	c = (t_color){0, 120, 80};
	t->tex_x = (1 + atan2(n.z, n.x) / M_PI) * 0.5;
	t->tex_y = acosf(n.y) / M_PI;
	t->s = t->tex_x * cos(t->angle) - t->tex_y * sin(t->angle);
	t->t = t->tex_y * cos(t->angle) + t->tex_x * sin(t->angle);
	return (c);
}

t_color			sepia(t_color col)
{
	int r;
	int g;
	int b;

	r = col.r;
	b = col.b;
	g = col.g;
	col.r = (int)((r * 0.393) + (g * 0.769) + (b * 0.189));
	col.g = (int)((r * 0.349) + (g * 0.686) + (b * 0.168));
	col.b = (int)((r * 0.272) + (g * 0.534) + (b * 0.131));
	return (col);
}

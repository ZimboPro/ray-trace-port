/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:46:31 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 12:42:31 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** allocates memory
*/
void			ft_planes(t_objects *obj, char **str, int i, int *j)
{
	*j = *j + 1;
	char * s = joinStr(str, i);
	plane(obj, s);
	free(s);
}

/*
 ** checks to see if ray intersects with plane
*/
void			int_plane(t_objects obj, float *d, t_ray ray)
{
	t_vector	di;
	t_vector	p;
	t_vector	uv;
	float		t;

	di = obj.dir;
	t = 0;
	di.w = 0;
	p = (t_vector){obj.dir.x * obj.dir.w, obj.dir.y * obj.dir.w,
		obj.dir.z * obj.dir.w, 0};
	di.w = calc_dp(p, di);
	uv = calc_unit_v(ray.v);
	t = 0;
	if (calc_dp(ray.v, di) != 0)
	{
		t = -(di.x * ray.sc.x + di.y * ray.sc.y + di.z *
				ray.sc.z + di.w);
		t = t / (di.x * uv.x + di.y * uv.y + di.z * uv.z);
		if (t > 0)
			*d = t;
	}
}

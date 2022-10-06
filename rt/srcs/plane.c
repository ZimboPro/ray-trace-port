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
 ** gets object details
*/

static void		ft_pln(int *i, char **str, t_objects *plane)
{
	char					**s;

	s = ft_strsplit(str[*i], ' ');
	plane->dir.x = (float)ft_atoi(s[0]);
	plane->dir.y = (float)ft_atoi(s[1]);
	plane->dir.z = (float)ft_atoi(s[2]);
	plane->dir.w = (float)ft_atoi(s[3]);
	ft_strarrdel(s);
	*i += 1;
	s = ft_strsplit(str[*i], ' ');
	plane->reflect = ((float)ft_atoi(s[0]) / 100);
	plane->refract = ft_atoi(s[1]);
	ft_strarrdel(s);
	*i += 1;
	s = ft_strsplit(str[*i], ' ');
	if (ft_atoi(s[0]))
		plane->c = ft_rand(plane->c);
	plane->pattern = ft_atoi(s[1]);
	plane->filter = ft_atoi(s[2]);
	ft_strarrdel(s);
	*i += 1;
	s = NULL;
}

/*
 ** allocates memory
*/

void			ft_planes(t_objects *obj, char **str, int i, int *j)
{
	*j = *j + 1;
	while (str[i] != NULL && ft_strstr(str[i], "Plane") == NULL)
		i++;
	i++;
	obj->circle = 0;
	obj->cone = 0;
	obj->cylinder = 0;
	obj->plane = 1;
	ft_pln(&i, str, obj);
	str_map_to_color(str[i], &obj->col);
	obj->c = (t_point){0, 0, 0, 0};
	obj->h = 0;
	obj->rad = 0;
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

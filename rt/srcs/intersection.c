/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 09:32:40 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/07 07:52:14 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** finds corresponding ray intersection function
*/
static void	intersect(t_objects obj, float *d, t_ray ray)
{
	if (obj.type == Circle)
		int_circle(obj, d, ray);
	else if (obj.type == Cone)
		int_cone(obj, d, ray);
	else if (obj.type == Cylinder)
		int_cyl(obj, d, ray);
	else if (obj.type == Plane)
		int_plane(obj, d, ray);
}

/*
 ** finds closest intersection if any for ray
*/
int			intersection(t_obj obj, float *d, t_vector v, t_point p)
{
	float	dist;
	int		ind;
	int		i;
	t_ray	ray;

	*d = -1;
	i = 0;
	ind = -1;
	ray = (t_ray){p, v};
	while (i < obj.obj_total)
	{
		dist = -1;
		intersect(obj.objects[i], &dist, ray);
		if (dist != -1 && (dist < *d || *d == -1))
		{
			*d = dist;
			ind = i;
		}
		i++;
	}
	return (ind);
}

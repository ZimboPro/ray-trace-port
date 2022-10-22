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
#include <rt_rs.h>

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

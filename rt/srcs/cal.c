/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 10:01:51 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 15:42:49 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** gets ray shot from camera
*/

t_ray			ray(t_obj obj, float x, float y)
{
	t_ray	ray;

	x = (-obj.camera.h_fov + x * obj.camera.xdeg) * obj.camera.ar;
	y = obj.camera.h_fov - y * obj.camera.ydeg;
	ray.v = calc_addition(calc_multi(obj.camera.view, cos(x)), calc_multi(
				obj.camera.hor, sin(x)));
	ray.v = calc_addition(calc_multi(ray.v, cos(y)), calc_multi(obj.camera.up,
					sin(y)));
	ray.sc = calc_vect_to_point(obj.camera.c, ray.v, obj.camera.dist);
	return (ray);
}

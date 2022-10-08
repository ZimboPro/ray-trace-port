/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 08:54:00 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 08:54:03 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** calculates the unit distance, the centre of view plane and aspect ratio
*/
void		camera_corners(t_camera *cam)
{
	cam->scale = tan((cam->h_fov / 2) * (M_PI / 180));
	cam->dist = (float)(cam->height >> 1) / cam->scale;
	cam->ar = cam->width / (float)cam->height;
	cam->ydeg = cam->h_fov * (M_PI / 180) / (float)(cam->height - 1);
	cam->xdeg = cam->h_fov * (M_PI / 180) / (float)(cam->width - 1);
	cam->h_fov *= 0.5f * (M_PI / 180);
}

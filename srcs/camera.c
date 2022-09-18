/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:46:47 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/12 14:36:54 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** gets new vectors and coordinates
*/

static void	cam_vect(t_camera *cam, t_point p)
{
	cam->c = p;
	cam->view = calc_unit_v(calc_p_to_v(cam->c, (t_point){0, 0, 0, 1}));
	cam->hor = calc_unit_v(calc_cross_product(cam->view,
				(t_vector){0, 1, 0, 0}));
	cam->up = calc_unit_v(calc_cross_product(cam->hor, cam->view));
}

/*
 ** gets camera position
*/

static void	ft_cam(int *i, char **str, t_camera *cam)
{
	char		**s;
	t_point		p;

	s = ft_strsplit(str[*i], ' ');
	p.x = (float)ft_atoi(s[0]);
	free(s[0]);
	p.y = (float)ft_atoi(s[1]);
	free(s[1]);
	p.z = (float)ft_atoi(s[2]);
	p.w = 1.0f;
	free(s[2]);
	free(s);
	if (cam->c.x != p.x || cam->c.y != p.y || cam->c.z != p.z)
		cam_vect(cam, p);
}

/*
 ** initailising the camera
*/

void		init_cam(t_camera *cam)
{
	cam->c = (t_point){0, 0, 0, 1};
	cam->up = (t_vector){0, 1, 0, 0};
	cam->view = (t_vector){0, 0, -1, 0};
	cam->hor = (t_vector){1, 0, 0, 0};
}

/*
 ** gets back ground color
*/

static void	background_color(t_camera *cam, char *str)
{
	char	**s;

	s = ft_strsplit(str, ' ');
	cam->bg.r = ft_atoi(s[0]);
	cam->bg.g = ft_atoi(s[1]);
	cam->bg.b = ft_atoi(s[2]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** gets camera details
*/

t_camera	ft_camera(char **str)
{
	t_camera	cam;
	int			i;
	char		**s;

	i = 0;
	init_cam(&cam);
	while (ft_strstr(str[i], "Camera") == NULL)
		i++;
	i++;
	ft_cam(&i, str, &cam);
	i++;
	s = ft_strsplit(str[i], ' ');
	cam.width = ft_atoi(s[0]);
	cam.height = ft_atoi(s[1]);
	cam.h_fov = (float)ft_atoi(s[2]);
	ft_strarrdel(s);
	i++;
	cam.mode = ft_atoi(str[i]);
	i++;
	background_color(&cam, str[i]);
	camera_corners(&cam);
	return (cam);
}

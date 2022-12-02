/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:27:31 by syoung            #+#    #+#             */
/*   Updated: 2017/09/19 09:27:39 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** checks to see if entry for camera is correct
*/

void	check_camera(char **str, int i, int *chk)
{
	int		lines;

	lines = 1;
	while ((ft_isdigit(str[i + lines][0]) == 1 || str[i + lines][0] == '-')
			&& lines < 5)
		lines++;
	if (lines != 5)
	{
		ft_putendl("Error: missing one or more elements in Camera");
		*chk = 0;
	}
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in name");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in coordinates");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in screen size angle and fov");
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in camera mode");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in background color");
}

/*
 ** checks to see if entry for light is correct
*/

void	check_light(char **str, int i, int *chk)
{
	int		lines;
	char	**s;
	int		t;

	if ((t = cnt_space(str[i], &i, chk, 2)) != 1)
		ft_putendl("Error in name");
	else
	{
		s = ft_strsplit(str[i - 1], ' ');
		t = ft_atoi(s[1]);
		ft_strarrdel(s);
		s = NULL;
	}
	lines = 1;
	while (ft_isdigit(str[i + lines][0]) == 1 && lines < t)
		lines++;
	if (lines != t)
		*chk = 0;
	lines = 0;
	while (lines < t)
	{
		if (cnt_space(str[i], &i, chk, 2) != 1)
			ft_putendl("Error in coordinates");
		lines++;
	}
}

/*
 ** checks values and outputs error if any
*/

int		valid_count(int c, int l, int o)
{
	int		chk;

	chk = 1;
	if (c != 1)
	{
		if (c == 0)
			ft_putendl("No camera");
		else
			ft_putendl("Too many cameras");
		chk = 0;
	}
	if (l == 0)
	{
		ft_putendl("No light");
		chk = 0;
	}
	if (o == 0)
	{
		ft_putendl("No object");
		chk = 0;
	}
	return (chk);
}

/*
 ** checks to see if there is a light and camera and at least one object
*/

int		valid(char **str)
{
	int		i;
	int		o;
	int		c;
	int		l;

	i = 0;
	o = 0;
	c = 0;
	l = 0;
	while (str[i])
	{
		if (ft_strstr(str[i], "Camera") != NULL)
			c++;
		else if (ft_strstr(str[i], "Light") != NULL)
			l++;
		else if (ft_strstr(str[i], "Circle") != NULL ||
				ft_strstr(str[i], "Cone") != NULL ||
				ft_strstr(str[i], "Cylinder") != NULL ||
				ft_strstr(str[i], "Plane") != NULL)
			o++;
		i++;
	}
	return (valid_count(c, l, o));
}

/*
 ** checks to see if map is valid
*/

int		map_check(char **str)
{
	int		i;
	int		chk;

	i = 0;
	chk = valid(str);
	while (str[i] != NULL)
	{
		if (ft_strstr(str[i], "Circle") != NULL)
			check_circle(str, i, &chk);
		else if (ft_strstr(str[i], "Cone") != NULL)
			check_cone(str, i, &chk);
		else if (ft_strstr(str[i], "Plane") != NULL)
			check_plane(str, i, &chk);
		else if (ft_strstr(str[i], "Cylinder") != NULL)
			check_cylinder(str, i, &chk);
		else if (ft_strstr(str[i], "Camera") != NULL)
			check_camera(str, i, &chk);
		else if (ft_strstr(str[i], "Lights") != NULL)
			check_light(str, i, &chk);
		i++;
	}
	if (chk != 1)
		return (0);
	return (1);
}

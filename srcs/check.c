/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:46:51 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/12 13:55:10 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** count the number of spaces in a string and compare it with the expected
 ** result
*/

int		cnt_space(char *str, int *j, int *chk, int value)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 32)
			cnt++;
		i++;
	}
	*j += 1;
	if (cnt != value)
	{
		*chk = 0;
		return (0);
	}
	return (1);
}

/*
 ** checks to see if entry for sphere is correct
*/

void	check_circle(char **str, int i, int *chk)
{
	int		lines;

	lines = 1;
	while ((ft_isdigit(str[i + lines][0]) == 1 || str[i + lines][0] == '-')
			&& lines < 6)
		lines++;
	if (lines != 6)
	{
		ft_putendl("Error: missing one or more elements in Circle");
		*chk = 0;
	}
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in name");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in coordinates");
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in radius");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in reflection and refraction");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color");
	if (cnt_space(str[i], &i, chk, 3) != 1)
		ft_putendl("Error in color options");
}

/*
 ** checks to see if entry for cone is correct
*/

void	check_cone(char **str, int i, int *chk)
{
	int		lines;

	lines = 1;
	while ((ft_isdigit(str[i + lines][0]) == 1 || str[i + lines][0] == '-')
			&& lines < 7)
		lines++;
	if (lines != 7)
	{
		ft_putendl("Error: missing one or more elements in Cone");
		*chk = 0;
	}
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in name");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in coordinates");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in direction");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in radius and hieght");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in reflection and refraction");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color options");
}

/*
 ** checks to see if entry for cylinder is correct
*/

void	check_cylinder(char **str, int i, int *chk)
{
	int		lines;

	lines = 1;
	while ((ft_isdigit(str[i + lines][0]) == 1 || str[i + lines][0] == '-')
			&& lines < 7)
		lines++;
	if (lines != 7)
	{
		ft_putendl("Error: missing one or more elements in Cylinder");
		*chk = 0;
	}
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in name");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in coordinates");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in direction");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in radius and hieght");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in reflection and refraction");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color options");
}

/*
 ** checks to see if entry for plane is correct
*/

void	check_plane(char **str, int i, int *chk)
{
	int		lines;

	lines = 1;
	while ((ft_isdigit(str[i + lines][0]) == 1 || str[i + lines][0] == '-')
			&& lines < 5)
		lines++;
	if (lines != 5)
	{
		ft_putendl("Error: missing one or more elements in Plane");
		*chk = 0;
	}
	if (cnt_space(str[i], &i, chk, 0) != 1)
		ft_putendl("Error in name");
	if (cnt_space(str[i], &i, chk, 3) != 1)
		ft_putendl("Error in coordinates");
	if (cnt_space(str[i], &i, chk, 1) != 1)
		ft_putendl("Error in reflection and refraction");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color");
	if (cnt_space(str[i], &i, chk, 2) != 1)
		ft_putendl("Error in color options");
}

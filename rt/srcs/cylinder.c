/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:46:24 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/12 15:32:41 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** get object details
*/

static void		ft_cyl_helper(int *i, char **str, t_objects *cyl)
{
	char	**s;

	s = ft_strsplit(str[*i], ' ');
	cyl->c.x = (float)ft_atoi(s[0]);
	cyl->c.y = (float)ft_atoi(s[1]);
	cyl->c.z = (float)ft_atoi(s[2]);
	cyl->c.w = 1;
	ft_strarrdel(s);
	*i = *i + 1;
}

static void		ft_cyl(int *i, char **str, t_objects *cyl)
{
	char					**s;

	ft_cyl_helper(i, str, cyl);
	s = ft_strsplit(str[*i], ' ');
	cyl->dir.x = (float)ft_atoi(s[0]);
	cyl->dir.y = (float)ft_atoi(s[1]);
	cyl->dir.z = (float)ft_atoi(s[2]);
	cyl->dir.w = 0;
	ft_strarrdel(s);
	*i = *i + 1;
	s = ft_strsplit(str[*i], ' ');
	cyl->rad = (float)ft_atoi(s[0]);
	cyl->h = (float)ft_atoi(s[1]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** gets object color
*/

static void		ft_cyl_options(char *str, t_objects *obj)
{
	char **s;

	s = ft_strsplit(str, ' ');
	if (ft_atoi(s[0]) == 1)
		obj->c = ft_rand(obj->c);
	obj->pattern = ft_atoi(s[1]);
	obj->filter = ft_atoi(s[2]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** alocates memory
*/

void			ft_cylinders(t_objects *obj, char **str, int i, int *j)
{
	char	**s;

	*j = *j + 1;
	while (ft_strstr(str[i], "Cylinder") == NULL)
		i++;
	i++;
	obj->circle = 0;
	obj->cone = 0;
	obj->cylinder = 1;
	obj->plane = 0;
	ft_cyl(&i, str, obj);
	i++;
	s = ft_strsplit(str[i], ' ');
	obj->reflect = ((float)ft_atoi(s[0]) / 100);
	obj->refract = ft_atoi(s[1]);
	ft_strarrdel(s);
	s = NULL;
	i++;
	str_map_to_color(str[i], &obj->col);
	i++;
	ft_cyl_options(str[i], obj);
}

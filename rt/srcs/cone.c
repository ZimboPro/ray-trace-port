/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:45:56 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/13 13:22:39 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** get object details
*/

static void		ft_cone_helper(int *i, char **str, t_objects *obj)
{
	char	**s;

	s = ft_strsplit(str[*i], ' ');
	obj->c.x = (float)ft_atoi(s[0]);
	obj->c.y = (float)ft_atoi(s[1]);
	obj->c.z = (float)ft_atoi(s[2]);
	obj->c.w = 1;
	ft_strarrdel(s);
	*i = *i + 1;
}

static void		ft_cone(int *i, char **str, t_objects *obj)
{
	char					**s;

	ft_cone_helper(i, str, obj);
	s = ft_strsplit(str[*i], ' ');
	obj->dir.x = (float)ft_atoi(s[0]);
	obj->dir.y = (float)ft_atoi(s[1]);
	obj->dir.z = (float)ft_atoi(s[2]);
	obj->dir.w = 0;
	ft_strarrdel(s);
	*i = *i + 1;
	s = ft_strsplit(str[*i], ' ');
	obj->rad = (float)ft_atoi(s[0]);
	obj->h = (float)ft_atoi(s[1]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** gets object colors
*/

static void		ft_cone_color(char *str, t_objects *obj)
{
	char	**s;

	s = ft_strsplit(str, ' ');
	obj->col.r = ft_atoi(s[0]);
	obj->col.g = ft_atoi(s[1]);
	obj->col.b = ft_atoi(s[2]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** allocates memory
*/

static void		ft_cone_options(char *str, t_objects *obj)
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

void			ft_cones(t_objects *obj, char **str, int i, int *j)
{
	char	**s;

	*j = *j + 1;
	while (ft_strstr(str[i], "Cone") == NULL)
		i++;
	i++;
	obj->circle = 0;
	obj->cone = 1;
	obj->cylinder = 0;
	obj->plane = 0;
	ft_cone(&i, str, obj);
	i++;
	s = ft_strsplit(str[i], ' ');
	obj->reflect = ((float)ft_atoi(s[0]) / 100);
	obj->refract = ft_atoi(s[1]);
	ft_strarrdel(s);
	s = NULL;
	i++;
	ft_cone_color(str[i], obj);
	i++;
	ft_cone_options(str[i], obj);
}

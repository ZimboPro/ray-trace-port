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

static void		ft_cone(int *i, char **str, t_objects *obj)
{
	char					**s;

	str_map_to_vec4_def(str[*i], &obj->c);
	*i = *i + 1;
	str_map_to_vec4_def(str[*i], &obj->dir);
	*i = *i + 1;
	s = ft_strsplit(str[*i], ' ');
	obj->rad = (float)ft_atoi(s[0]);
	obj->h = (float)ft_atoi(s[1]);
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
	obj->type = Cone;
	ft_cone(&i, str, obj);
	i++;
	s = ft_strsplit(str[i], ' ');
	obj->reflect = ((float)ft_atoi(s[0]) / 100);
	obj->refract = ft_atoi(s[1]);
	ft_strarrdel(s);
	s = NULL;
	i++;
	str_map_to_color(str[i], &obj->col);
	i++;
	ft_cone_options(str[i], obj);
}

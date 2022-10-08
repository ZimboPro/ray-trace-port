/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:45:31 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 12:49:01 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_rs.h>


static void		ft_circ(int *i, char **str, t_objects *obj)
{
	char					**s;

	str_map_to_vec4_def(str[*i], &obj->c);
	*i = *i + 1;
	obj->rad = (float)ft_atoi(str[*i]);
	*i = *i + 1;
	s = ft_strsplit(str[*i], ' ');
	obj->reflect = ((float)ft_atoi(s[0]) / 100);
	obj->refract = ft_atoi(s[1]);
	ft_strarrdel(s);
	*i = *i + 1;
	str_map_to_color(str[*i], &obj->col);
	*i = *i + 1;
	s = ft_strsplit(str[*i], ' ');
	if (ft_atoi(s[0]))
		obj->c = ft_rand(obj->c);
	obj->pattern = ft_atoi(s[1]);
	obj->filter = ft_atoi(s[2]);
	obj->texmap = ft_strdup(s[3]);
	ft_strarrdel(s);
	s = NULL;
}

/*
 ** gets values for circle
*/
void			ft_circles(t_objects *obj, char **str, int i, int *j)
{
	*j = *j + 1;
	while (ft_strstr(str[i], "Circle") == NULL)
		i++;
	i++;
	obj->type = Circle;
	ft_circ(&i, str, obj);
	obj->h = 0;
	obj->dir = (t_vector){0, 0, 0, 0};
}

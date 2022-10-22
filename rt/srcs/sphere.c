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


// static void		ft_circ(int *i, char **str, t_objects *obj)
// {
// 	char					**s;

// 	str_map_to_vec4_def(str[*i], &obj->c);
// 	*i = *i + 1;
// 	obj->rad = (float)ft_atoi(str[*i]);
// 	*i = *i + 1;
// 	s = ft_strsplit(str[*i], ' ');
// 	obj->reflect = ((float)ft_atoi(s[0]) / 100);
// 	obj->refract = ft_atoi(s[1]);
// 	ft_strarrdel(s);
// 	*i = *i + 1;
// 	str_map_to_color(str[*i], &obj->col);
// 	*i = *i + 1;
// 	s = ft_strsplit(str[*i], ' ');
// 	if (ft_atoi(s[0]))
// 		obj->c = ft_rand(obj->c);
// 	obj->pattern = ft_atoi(s[1]);
// 	obj->filter = ft_atoi(s[2]);
// 	obj->texmap = ft_strdup(s[3]);
// 	ft_strarrdel(s);
// 	s = NULL;
// }

/*
 ** gets values for circle
*/
void			ft_circles(t_objects *obj, char **str, int i, int *j)
{
	char * s = ft_strnew(0);
	*j = *j + 1;
	while (ft_strlen(str[i]) != 0) {
		char * t = ft_strjoin( ft_strjoin(s, "\n"), str[i]);
		free(s);
		s = t;
		i++;
	}
	ft_circle(obj, s);
	obj->texmap = "NULL";
}

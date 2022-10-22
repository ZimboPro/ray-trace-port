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

static void		ft_cyl(int *i, char **str, t_objects *cyl)
{
	char					**s;

	str_map_to_vec4_def(str[*i], &cyl->c);
	*i = *i + 1;
	str_map_to_vec4_def(str[*i], &cyl->dir);
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
	char	*s = joinStr(str, i);

	*j = *j + 1;
	cylinder(obj, s);
	free(s);
}

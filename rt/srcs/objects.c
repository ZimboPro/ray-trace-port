/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 08:54:07 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 13:26:15 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** updates map with unit distance
*/
static void	ft_update_map(t_obj *obj, float d)
{
	int		i;

	i = 0;
	while (i < obj->obj_total)
	{
		if (obj->objects[i].type == Plane)
			obj->objects[i].dir.w *= d;
		if (obj->objects[i].type != Plane)
		{
			obj->objects[i].c = calc_multi(obj->objects[i].c, d);
			obj->objects[i].rad *= d;
		}
		if (obj->objects[i].type != Plane && obj->objects[i].type != Circle)
			obj->objects[i].h *= d;
		i++;
	}
	i = 0;
	obj->camera.c = calc_multi(obj->camera.c, d);
	while (i < obj->light)
	{
		obj->lights[i].c = calc_multi_vec(obj->lights[i].c, d);
		i++;
	}
}

/*
 ** if there is the respective object it the retrieves it's detatils
*/
void		obj_assign(t_obj *obj, char **str)
{
	int		i;
	int		j;
	int		t;

	i = 0;
	j = 0;
	t = obj->obj_total;
	while (str[i] != NULL && j < t)
	{
		if (ft_strstr(str[i], "Circle") != NULL) {
			char * s = joinStr(str, i);
			ft_circle(&(obj->objects[j]), s);
			obj->objects[j].texmap = "NULL";
			free(s);
		} else if (ft_strstr(str[i], "Cone") != NULL) {
			char	*s = joinStr(str, i);
			cone(&(obj->objects[j]), s);
			j += 1;
			free(s);
		} else if (ft_strstr(str[i], "Cylinder") != NULL) {
			char	*s = joinStr(str, i);
			cylinder(&(obj->objects[j]), s);
			j += 1;
			free(s);
		} else if (ft_strstr(str[i], "Plane") != NULL) {
			char	*s = joinStr(str, i);
			plane(&(obj->objects[j]), s);
			j += 1;
			free(s);
		}
		i++;
	}
	obj->progress = 0;
	obj->first = 0;
	obj->lights = ft_lights(obj->light, str);
	obj->camera = ft_camera(str);
	ft_update_map(obj, obj->camera.dist);
}

/*
 ** gets the amount of that object
*/
int			ft_cnt(char *str)
{
	char	**s;
	int		i;

	s = ft_strsplit(str, ' ');
	i = ft_atoi(s[1]);
	ft_strarrdel(s);
	return (i);
}

/*
 ** gets amount of each object
*/
t_obj		objects(char **str)
{
	t_obj	object;
	int		i;

	i = 0;
	object.obj_total = 0;
	while (str[i] != NULL)
	{
		if (ft_strstr(str[i], "Circle") != NULL)
			object.obj_total = object.obj_total + 1;
		else if (ft_strstr(str[i], "Cone") != NULL)
			object.obj_total = object.obj_total + 1;
		else if (ft_strstr(str[i], "Cylinder") != NULL)
			object.obj_total = object.obj_total + 1;
		else if (ft_strstr(str[i], "Plane") != NULL)
			object.obj_total = object.obj_total + 1;
		else if (ft_strstr(str[i], "Light") != NULL)
			object.light = ft_cnt(str[i]);
		i++;
	}
	object.objects = (t_objects *)malloc(sizeof(t_objects) * object.obj_total);
	i = -1;
	while (++i < object.obj_total)
		ft_bzero(&(object.objects[i]), sizeof(t_objects));
	return (object);
}


char * joinStr(char **str, int i) {
	char * s = ft_strnew(0);
	while (str[i] != NULL && ft_strlen(str[i]) != 0) {
		char * t = ft_strjoin( ft_strjoin(s, "\n"), str[i]);
		free(s);
		s = t;
		i++;
	}
	return s;
}

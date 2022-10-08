/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:46:58 by lde-jage          #+#    #+#             */
/*   Updated: 2017/08/19 09:30:16 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** allocates memory for light(s)
*/
t_light		*ft_lights(int len, char **str)
{
	t_light		*lights;
	int			i;
	int			j;

	i = 0;
	while (ft_strstr(str[i], "Light") == NULL)
		i++;
	lights = (t_light *)malloc(sizeof(t_light) * len);
	j = 0;
	i++;
	while (str[i] != NULL && j < len)
	{
		str_map_to_vec3(str[i], &lights[j].c);
		lights[j].total = len;
		i++;
		j++;
	}
	return (lights);
}

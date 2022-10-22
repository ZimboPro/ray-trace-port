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

/*
 ** gets values for circle
*/
void			ft_circles(t_objects *obj, char **str, int i, int *j)
{
	char * s = joinStr(str, i);
	*j = *j + 1;
	ft_circle(obj, s);
	obj->texmap = "NULL";
	free(s);
}

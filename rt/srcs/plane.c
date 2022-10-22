/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:46:31 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 12:42:31 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** allocates memory
*/
void			ft_planes(t_objects *obj, char **str, int i, int *j)
{
	*j = *j + 1;
	char * s = joinStr(str, i);
	plane(obj, s);
	free(s);
}


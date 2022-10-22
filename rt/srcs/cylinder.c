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
 ** alocates memory
*/
void			ft_cylinders(t_objects *obj, char **str, int i, int *j)
{
	char	*s = joinStr(str, i);

	*j = *j + 1;
	cylinder(obj, s);
	free(s);
}

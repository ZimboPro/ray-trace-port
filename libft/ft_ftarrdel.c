/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftarrdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 10:56:53 by lde-jage          #+#    #+#             */
/*   Updated: 2017/08/17 10:57:10 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_ftarrdel(float **pts, int row)
{
	int		i;

	if (pts != NULL)
	{
		i = 0;
		while (i < row)
		{
			free(pts[i]);
			i++;
		}
		free(pts);
		pts = NULL;
	}
}

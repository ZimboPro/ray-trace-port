/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 10:59:22 by lde-jage          #+#    #+#             */
/*   Updated: 2017/07/07 07:38:42 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_arrdel(int **pts, int row)
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

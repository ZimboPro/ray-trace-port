/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 07:44:24 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 14:43:14 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

double		**ft_dbarrnew(int row, int col)
{
	double		**arr;
	int			i;

	i = 0;
	arr = (double **)malloc(sizeof(double *) * row);
	ft_bzero(&arr, sizeof(double *) * row);
	if (arr == NULL)
		return (NULL);
	while (i < row)
	{
		arr[i] = (double *)malloc(sizeof(double) * col);
		ft_bzero(&(arr[i]), sizeof(double) * col);
		if (arr[i] == NULL)
			return (NULL);
		i++;
	}
	return (arr);
}

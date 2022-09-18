/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 15:43:53 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 14:42:56 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		**ft_intarrnew(int row, int col)
{
	int		**arr;
	int		i;

	i = 0;
	arr = (int **)malloc(sizeof(int *) * row);
	ft_bzero(&arr, sizeof(int *) * row);
	if (arr == NULL)
		return (NULL);
	while (i < row)
	{
		arr[i] = (int *)malloc(sizeof(int) * col);
		ft_bzero(&arr, sizeof(int) * col);
		if (arr[i] == NULL)
			return (NULL);
		i++;
	}
	return (arr);
}

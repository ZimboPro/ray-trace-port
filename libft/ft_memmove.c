/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:53:30 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/08 14:15:07 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	temp[n + 1];

	i = 0;
	while (i < n)
	{
		temp[i] = ((unsigned char *)str2)[i];
		i++;
	}
	while (i > 0)
	{
		i--;
		((unsigned char *)str1)[i] = temp[i];
	}
	return (str1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:52:32 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/20 09:50:46 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	check;

	i = 0;
	temp = (unsigned char *)str;
	check = (unsigned char)c;
	while (i < n)
	{
		if (temp[i] == check)
			return (&temp[i]);
		i++;
	}
	return (NULL);
}

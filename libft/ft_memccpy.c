/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:52:19 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/01 14:08:18 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*s;
	unsigned char	t;

	i = 0;
	t = (unsigned char)c;
	dst = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		dst[i] = s[i];
		if (s[i] == t)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}

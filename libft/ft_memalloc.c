/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:10:14 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/20 09:39:02 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*mem;

	i = 0;
	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	while (i < size)
	{
		((unsigned char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}

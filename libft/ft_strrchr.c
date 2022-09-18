/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:56:59 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/08 12:44:49 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		pos;
	char	*temp;

	i = 0;
	pos = -10;
	temp = (char *)str;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			pos = i;
		i++;
	}
	if (c == '\0' && str[i] == '\0')
		return (&temp[i]);
	if (pos < 0)
		return (NULL);
	return (&temp[pos]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:54:26 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/08 12:38:30 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*temp;
	char	t;

	i = 0;
	t = c;
	temp = (char *)str;
	while (str[i] != '\0')
	{
		if (str[i] == t)
			return (&temp[i]);
		i++;
	}
	if (c == '\0' && str[i] == '\0')
		return (&temp[i]);
	return (NULL);
}

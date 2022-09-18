/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 08:34:23 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/20 09:51:34 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpy(char const *s, char *d, int i, int end)
{
	int	j;

	j = 0;
	while (i <= end)
	{
		d[j] = s[i];
		j++;
		i++;
	}
	d[j] = '\0';
	return (d);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		begin;
	int		end;
	char	*new;

	if (s == NULL)
		return (NULL);
	i = 0;
	while ((s[i] == 32 || s[i] == 9 || s[i] == 10) && s[i] != '\0')
		i++;
	begin = i;
	while (s[i] != '\0')
	{
		if (s[i] != 32 && s[i] != 9 && s[i] != 10)
			end = i;
		i++;
	}
	new = (char *)malloc(end - begin + 2);
	if (new == NULL)
		return (NULL);
	return (ft_cpy(s, new, begin, end));
}

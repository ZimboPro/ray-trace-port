/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:57:15 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/02 17:20:10 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_l(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_chk(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	i = ft_l(haystack) - 1;
	n = ft_l(needle) - 1;
	temp = (char *)haystack;
	while (i >= 0)
	{
		j = n;
		while (j >= 0 && temp[i] == needle[j] && j <= i)
		{
			if (j == 0)
				return (&temp[i]);
			j--;
			i--;
		}
		i--;
	}
	return (NULL);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = (char *)haystack;
	if (needle[i] == '\0')
		return (temp);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return (&temp[i - j]);
		i++;
	}
	return (ft_chk(haystack, needle));
}

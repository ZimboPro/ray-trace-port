/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 08:22:47 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/05 16:08:13 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*ft_add(const char *s, char c, int *i)
{
	char	*str;
	int		start;
	int		end;

	start = *i;
	while (s[*i] != '\0' && s[*i] != c)
		*i = *i + 1;
	end = *i;
	str = ft_strnew(end - start);
	*i = start;
	while (*i < end)
	{
		str[*i - start] = (char)s[*i];
		*i = *i + 1;
	}
	str[*i - start] = '\0';
	return (str);
}

static int	ft_wrd_cnt(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (s[i] != c)
		cnt++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cnt++;
		i++;
	}
	return (cnt);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		wrd_cnt;
	char	**str;

	if (s == NULL)
		return (NULL);
	wrd_cnt = ft_wrd_cnt(s, c);
	if ((str = (char **)malloc((sizeof(char *)) * (wrd_cnt + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < wrd_cnt)
	{
		if (s[i] != c)
		{
			str[j] = ft_add(s, c, &i);
			j++;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}

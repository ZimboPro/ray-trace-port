/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 10:23:11 by exam              #+#    #+#             */
/*   Updated: 2017/08/22 18:22:59 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_cnt(int nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		if (nbr < 0)
		{
			i = 2;
			nbr = nbr / -10;
		}
		else
		{
			i++;
			nbr = nbr / 10;
		}
	}
	return (i);
}

char		*ft_itoa(int nbr)
{
	char	*str;
	int		cnt;
	int		chk;

	cnt = ft_cnt(nbr);
	str = (char *)malloc(sizeof(char *) * (cnt + 1));
	chk = 0;
	str[cnt] = '\0';
	if (nbr < 0)
	{
		chk = 1;
		str[0] = '-';
		str[cnt - 1] = 48 - (nbr % 10);
		nbr = nbr / -10;
		cnt--;
	}
	while (cnt - chk - 1 >= 0)
	{
		str[cnt - 1] = (nbr % 10) + 48;
		nbr = nbr / 10;
		cnt--;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:49:59 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/30 09:40:23 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MIN -9223372036854775807LL
#define MAX 9223372036854775807LL

static int	ft_value(const char *str, int i, long long int value)
{
	long long int	check;
	int				temp;
	long long int	tot;
	long long result;

	check = 0;
	tot = 0;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		check = 1;
		temp = ((int)str[i]) - 48;
		tot = (tot * 10) + temp;
		i++;
	}
	result = value * check * tot;
	if (value == 1 && !result)
		return (0);
	if (value == -1 && !result)
		return (-1);
	if (result > MAX ||
			result < MIN)
		return (0);
	return result;
}

int			ft_atoi(const char *str)
{
	long long int	value;
	int				i;

	i = 0;
	value = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 45 || (str[i] >= 48 && str[i] <= 57) || str[i] == 43)
			break ;
		if (str[i] != 9 && str[i] != 10 && str[i] != 32
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	if (str[i + 1] >= 48 && str[i + 1] <= 57 && str[i] == 45)
		value = ft_value(str, i + 1, -1);
	else if (str[i + 1] >= 48 && str[i + 1] <= 57 && str[i] == 43)
		value = ft_value(str, i + 1, 1);
	else if (str[i] >= 48 && str[i] <= 57)
		value = ft_value(str, i, value);
	else
		return (0);
	return (value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 08:54:07 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 13:26:15 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** gets the amount of that object
*/
int			ft_cnt(char *str)
{
	char	**s;
	int		i;

	s = ft_strsplit(str, ' ');
	i = ft_atoi(s[1]);
	ft_strarrdel(s);
	return (i);
}

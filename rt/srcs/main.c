/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 08:48:09 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/15 14:43:32 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int ac, char *av[])
{
	if (ac != 2 && ac != 3)
	{
		ft_putendl("Usage ./RTv1 map");
		ft_putendl("OR");
		ft_putendl("Usage ./RTv1 map -a");
	}
	else if (ac == 3 && ft_strcmp(av[2], "-a") != 0)
		ft_putendl("Error: flag needs to be -a");
	else
	{
		if (ac == 2)
			sequence(av[1]);
		else
			aa_seq(av[1]);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 10:04:15 by syoung            #+#    #+#             */
/*   Updated: 2017/09/12 10:04:23 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** Linear-feedback shift register
*/
t_point	ft_rand(t_point p)
{
	unsigned				bit;
	int						tmp;
	static unsigned short	lfsr = 0xACF1u;

	p.x = 0;
	p.y = 0;
	while (1)
	{
		bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
		lfsr = (lfsr >> 1) | (bit << 15);
		tmp = lfsr;
		tmp = tmp % (FT_RAND_MAX + 1 - 0) + 0;
		if (tmp % 2 == 0)
			tmp *= -1;
		if (p.x == 0)
		{
			p.x = tmp;
		}
		else if (p.y == 0)
		{
			p.y = tmp;
			break ;
		}
	}
	return (p);
}

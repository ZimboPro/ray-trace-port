/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 14:31:00 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/08 13:40:42 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** multiplication 4x4 * 4x1
*/

t_vector		calc_con(t_vector b, float **a)
{
	t_vector	ans;

	ans.x = b.x * a[0][0] + b.y * a[1][0] + b.z * a[2][0] + b.w * a[3][0];
	ans.y = b.x * a[0][1] + b.y * a[1][1] + b.z * a[2][1] + b.w * a[3][1];
	ans.z = b.x * a[0][2] + b.y * a[1][2] + b.z * a[2][2] + b.w * a[3][2];
	ans.w = b.x * a[0][3] + b.y * a[1][3] + b.z * a[2][3] + b.w * a[3][3];
	return (ans);
}

/*
 ** dot product of 2 4x4 matrices
*/

float			**calc_trans(float **a, float **b)
{
	float	**ans;
	int		i;
	int		j;

	ans = ft_ftarrnew(4, 4);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ans[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] *
				b[2][j] + a[i][3] * b[3][j];
			j++;
		}
		i++;
	}
	return (ans);
}

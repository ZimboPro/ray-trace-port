/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:47:51 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/08 15:11:01 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** rotation in degrees
*/

float		**rotation(float x, float y, float z)
{
	float	**rot;

	rot = ft_ftarrnew(4, 4);
	rot[0][0] = cos(y) * cos(z);
	rot[0][1] = cos(y) * sin(z);
	rot[0][2] = -sin(y);
	rot[0][3] = 0;
	rot[1][0] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
	rot[1][1] = cos(x) * cos(z) + sin(x) * sin(y) * sin(z);
	rot[1][2] = sin(x) * cos(y);
	rot[1][3] = 0;
	rot[2][0] = -sin(x) * cos(z) + cos(x) * sin(y) * sin(z);
	rot[2][1] = -sin(x) * cos(z) + cos(x) * sin(y) * sin(z);
	rot[2][2] = cos(x) * cos(y);
	rot[2][3] = 0;
	rot[3][0] = 0;
	rot[3][1] = 0;
	rot[3][2] = 0;
	rot[3][3] = 1;
	return (rot);
}

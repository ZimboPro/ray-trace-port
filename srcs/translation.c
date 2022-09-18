/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 11:47:43 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/08 11:11:09 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** translation
*/

float		**translation(float tx, float ty, float tz)
{
	float	**trans;

	trans = ft_ftarrnew(4, 4);
	trans[0][0] = 1.0f;
	trans[0][1] = 0.0f;
	trans[0][2] = 0.0f;
	trans[0][3] = 0.0f;
	trans[1][0] = 0.0f;
	trans[1][1] = 1.0f;
	trans[1][2] = 0.0f;
	trans[1][3] = 0.0f;
	trans[2][0] = 0.0f;
	trans[2][1] = 0.0f;
	trans[2][2] = 1.0f;
	trans[2][3] = 0.0f;
	trans[3][0] = tx;
	trans[3][1] = ty;
	trans[3][2] = tz;
	trans[3][3] = 1.0f;
	return (trans);
}

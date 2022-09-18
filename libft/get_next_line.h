/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 13:43:54 by lde-jage          #+#    #+#             */
/*   Updated: 2017/07/06 16:31:12 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

# define BUF_SIZE 5

typedef struct	s_gnl
{
	void		*buf;
	char		**str;
	int			ret;
	int			fd_temp;
	int			line;
	int			cur;
}				t_gnl;

typedef struct	s_stdin
{
	char		*overflow;
}				t_stdin;

int				get_next_line(const int fd, char **line);

#endif

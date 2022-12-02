/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 15:50:29 by lde-jage          #+#    #+#             */
/*   Updated: 2017/09/04 16:24:22 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 ** opens map
*/

static int	ft_open(char *str)
{
	int		fd;

	if ((fd = open(str, O_RDONLY)) == -1)
	{
		ft_putstr("Error opening: ");
		ft_putendl(str);
	}
	return (fd);
}

/*
 ** reads map into string array
*/

static char	**file_copy(int fd, int i)
{
	int		j;
	char	**str;

	j = 0;
	str = (char **)malloc(sizeof(char *) * (i + 1));
	while (get_next_line(fd, &str[j]) > 0)
		j++;
	str[j] = NULL;
	close(fd);
	return (str);
}

/*
 ** determines how many lines there are in map
*/

static int	ft_line(int fd)
{
	int		i;
	char	*s;

	i = 0;
	while (get_next_line(fd, &s) > 0)
	{
		free(s);
		i++;
	}
	return (i);
}

/*
 ** reads map into string array and checks if file will open
*/

char		**ft_read(char *str)
{
	int		fd;
	char	**s1;
	int		i;

	if ((fd = ft_open(str)) != -1)
	{
		i = ft_line(fd);
		close(fd);
		if ((fd = ft_open(str)) != -1)
		{
			s1 = file_copy(fd, i);
			return (s1);
		}
	}
	return (NULL);
}

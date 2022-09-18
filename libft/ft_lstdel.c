/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 14:31:01 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/08 08:28:29 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *t;

	t = *alst;
	if (t->next != NULL)
		ft_lstdel(&t->next, del);
	del(t->content, t->content_size);
	free(*alst);
	*alst = NULL;
	alst = NULL;
}

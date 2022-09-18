/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 11:16:37 by lde-jage          #+#    #+#             */
/*   Updated: 2017/06/08 12:27:52 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*t1;
	t_list	*t2;
	t_list	*first;

	if (lst == NULL)
		return (NULL);
	first = f(lst);
	if (first == NULL)
		return (NULL);
	t1 = first;
	lst = lst->next;
	while (lst != NULL)
	{
		t2 = f(lst);
		if (t2 == NULL)
			return (NULL);
		t1->next = t2;
		t1 = t2;
		lst = lst->next;
	}
	t1->next = NULL;
	return (first);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:54:04 by iestero-          #+#    #+#             */
/*   Updated: 2023/03/15 15:04:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_cont;

	new_lst = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		new_cont = ft_lstnew(f(lst -> content));
		if (!new_cont)
			ft_lstclear(&new_lst, del);
		ft_lstadd_back(&new_lst, new_cont);
		lst = lst -> next;
	}
	return (new_lst);
}

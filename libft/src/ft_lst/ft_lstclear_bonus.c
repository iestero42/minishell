/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:34:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/02 11:05:57 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;
	t_list	*aux_next;

	if (*lst)
	{
		aux = *lst;
		while (aux)
		{
			aux_next = aux -> next;
			del(aux -> content);
			free(aux);
			aux = aux_next;
		}
		*lst = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:18:00 by marvin            #+#    #+#             */
/*   Updated: 2023/01/16 11:20:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

void	ft_insert_node(t_tree **node, int key, void *content, int number)
{
	if (*node == NULL)
		(*node) = ft_new_node(key, content, number);
	else if (key > (*node)->key)
	{
		if ((*node)->right == NULL)
			(*node)->right = ft_new_node(key, content, number);
		else
			ft_insert_node(&(*node)->right, key, content, number);
	}
	else
	{
		if ((*node)->left == NULL)
			(*node)->left = ft_new_node(key, content, number);
		else
			ft_insert_node(&(*node)->left, key, content, number);
	}
}

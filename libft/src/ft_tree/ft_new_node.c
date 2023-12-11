/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:54:04 by marvin            #+#    #+#             */
/*   Updated: 2023/01/15 17:54:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

t_tree	*ft_new_node(int key, void *content, int number)
{
	t_tree	*node;

	node = (t_tree *) malloc(sizeof(t_tree));
	node->key = key;
	node->content = content;
	node->number = number;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

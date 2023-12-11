/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:25:11 by marvin            #+#    #+#             */
/*   Updated: 2023/01/15 17:25:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

t_tree	*ft_find_node(int key, t_tree *root)
{
	if (root == NULL)
		return (NULL);
	else
	{
		if (key == root->key)
			return (root);
		else
		{
			if (key < root->key)
				return (ft_find_node(key, root->left));
			else
				return (ft_find_node(key, root->right));
		}
	}
}

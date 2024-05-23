/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:01:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/17 15:17:20 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

void	ft_clean_tree(t_tree **root, void (*del)(void *))
{
	if (*root != NULL && (*root)->content && del)
		del((*root)->content);
	if (*root != NULL)
	{
		ft_clean_tree(&(*root)->left, del);
		ft_clean_tree(&(*root)->right, del);
		free(*root);
		*root = NULL;
	}
}

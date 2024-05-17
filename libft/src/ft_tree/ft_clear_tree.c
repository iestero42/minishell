/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:01:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/17 09:25:33 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

void	ft_clean_tree(t_tree **root, void (*del)(void *));
{
	if (*root->content)
		del(*root->content);
	if (*root != NULL)
	{
		ft_clean_tree(&(*root)->left);
		ft_clean_tree(&(*root)->right);
		free(*root);
		*root = NULL;
	}
}

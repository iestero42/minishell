/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:01:33 by marvin            #+#    #+#             */
/*   Updated: 2023/01/15 18:01:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

void	ft_clean_tree(t_tree **root)
{
	if (*root != NULL)
	{
		ft_clean_tree(&(*root)->left);
		ft_clean_tree(&(*root)->right);
		free(*root);
		*root = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:04:34 by marvin            #+#    #+#             */
/*   Updated: 2023/02/09 15:04:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_node
{
	void			*content;
	int				number;
	int				key;
	struct s_node	*left;
	struct s_node	*right;
}	t_tree;

t_tree			*ft_new_node(int key, void *content, int number);

t_tree			*ft_find_node(int key, t_tree *root);

void			ft_insert_node(t_tree **node, int key, void *content,
					int number);

void			ft_clean_tree(t_tree **root);

#endif
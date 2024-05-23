/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestParseCommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:17:40 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:44 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int main(void)
{
	char	*s;
	t_tree	*tree;

	printf("Test 1: cat hola || echo adios \n\n");
	tree = ft_new_node(0, NULL, 0);
	parse_command_new("cat hola || echo adios", NULL, 0, &tree);	
}
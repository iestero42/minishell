/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:35 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/22 08:33:28 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	error_operands(int count_paranthese, char **tokens)
{
	if (count_paranthese > 0)
	{	
		ft_putstr_fd("minishell: syntax error near 'newline'\n", 2);
		return (EXIT_FAILURE);
	}
	else if (count_paranthese < 0 || tokens[0] == NULL)
	{	
		ft_putstr_fd("minishell: syntax error near ')'\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

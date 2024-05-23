/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:35 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/23 10:00:00 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	error_parenthesis(int count_paranthese, char **tokens, int i)
{
	if (count_paranthese > 0)
	{	
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" 'newline'\n", 2);
		return (EXIT_FAILURE);
	}
	else if (count_paranthese < 0 || tokens[0] == NULL || (tokens[1] != NULL
			&& *tokens[1] == ')' && *tokens[0] == '('))
	{	
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
		return (EXIT_FAILURE);
	}
	else if (tokens[i] != NULL && *tokens[i] == ')' && *tokens[i + 1] != '|'
		&& *tokens[i + 1] != '&')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	error_operands(char **tokens)
{
	int	i;

	if (*tokens[0] == '|' || *tokens[0] == '&')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens[0], 2);
		ft_putstr_fd("'\n", 2);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '&')
		{
			if (*tokens[i + 1] == '|' || *tokens[i + 1] == '&')
			{
				ft_putstr_fd("minishell: syntax error near unexpected", 2);
				ft_putstr_fd(" token `", 2);
				ft_putstr_fd(tokens[i + 1], 2);
				ft_putstr_fd("'\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

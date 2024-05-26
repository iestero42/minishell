/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:35 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/26 10:31:03 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file errors2_bonus.c
 * @brief Contains additional functions for handling errors.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

static check_null_parantheses(char **tokens, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (*tokens[j] == '(' && *tokens[j + 1] == ')')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
			return (EXIT_FAILURE);
		}
		else if (*tokens[j] == '(' && *tokens[j + 1] != ')')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Handles parenthesis errors.
 *
 * @details
 * Prints an error message depending on the type of parenthesis error.
 *
 * @param count_paranthese The number of parentheses.
 * @param tokens The array of tokens.
 * @param i The current position in the array.
 * @return EXIT_FAILURE if there is an error, otherwise EXIT_SUCCESS.
 */
int	error_parenthesis(int count_paranthese, char **tokens, int i)
{
	if (count_paranthese < 0 || tokens[0] == NULL || (tokens[1] != NULL
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

/**
 * @brief 
 * Handles operand errors.
 *
 * @details
 * Prints an error message if there are unexpected '|' or '&' tokens.
 *
 * @param tokens The array of tokens.
 * @return EXIT_FAILURE if there is an error, otherwise EXIT_SUCCESS.
 */
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

/**
 * @brief 
 * Handles an error in command parsing.
 *
 * @details
 * Sets the command type to ERROR_COMMAND, clears the name and args,
 * and frees the tokens.
 *
 * @param cmd The command structure to modify.
 * @param tokens The tokens to free.
 * @return Always returns EXIT_SUCCESS.
 */
int	error_command(t_command *cmd, char **tokens)
{
	cmd->type = ERROR_COMMAND;
	cmd->name = NULL;
	cmd->args = NULL;
	double_free(tokens);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:35 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/28 14:19:53 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file errors2_bonus.c
 * @brief Contains additional functions for handling errors.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

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

void	check_err_heredoc(char *line, int n_line, char *delimiter)
{
	extern char	**environ;

	double_free(environ);
	if (line == NULL)
	{
		ft_putstr_fd("-minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(n_line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:35 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/06 14:51:26 by yunlovex         ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tokens[0], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '&')
		{
			if (*tokens[i + 1] == '|' || *tokens[i + 1] == '&')
			{
				ft_putstr_fd("minishell: syntax error near unexpected",
					STDERR_FILENO);
				ft_putstr_fd(" token `", STDERR_FILENO);
				ft_putstr_fd(tokens[i + 1], STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
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
int	error_command(t_command *cmd, char **tokens, int type_error)
{
	cmd->type = type_error;
	cmd->name = NULL;
	cmd->args = NULL;
	double_free(tokens);
	return (EXIT_SUCCESS);
}


/**
 * @brief 
 * Checks for heredoc termination without the specified delimiter.
 * 
 * @details
 * This function is called to check if a heredoc has been terminated by an
 * end-of-file (EOF) rather than the specified delimiter. If the line parameter
 * is NULL, indicating that EOF was reached before the delimiter, it prints a
 * warning message to STDERR indicating the line number where the heredoc
 * started and the expected delimiter.
 * 
 * @param line The current line read from the heredoc. If NULL,
 * 	EOF was reached.
 * @param n_line The line number where the heredoc started.
 * @param delimiter The delimiter string that was expected to terminate 
 * 	the heredoc.
 * 
 * @note This function always exits with EXIT_SUCCESS, which may not be
 * appropriate if you need to handle this as an actual error condition.
 */
void	check_err_heredoc(char *line, int n_line, char *delimiter)
{
	if (line == NULL)
	{
		ft_putstr_fd("-minishell: warning: here-document at line ",
			STDERR_FILENO);
		ft_putnbr_fd(n_line, STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
	exit(EXIT_SUCCESS);
}

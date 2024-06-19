/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:35:45 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/19 13:51:29 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_output_bonus.c
 * @brief Contains the functions for parsing output.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Opens a simple output redirection.
 *
 * @details
 * If the token contains an output redirection, it opens the file for writing
 * and sets the output redirection in the command structure.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	open_output_simple(char **tokens, t_command *cmd,
		char *control)
{
	if (tokens[0][0] == OUTPUT_REDIR)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && tokens[1][0] != OUTPUT_REDIR
			&& tokens[1][0] != INPUT_REDIR && *tokens[1] != ENVP_VAR)
		{
			cmd->output_redirect = open(tokens[1], O_RDWR
					| O_CREAT | O_TRUNC, 0666);
			if (cmd->output_redirect < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				if (!*tokens[1])
					ft_putstr_fd(": ", STDERR_FILENO);
				perror(tokens[1]);
			}
			*tokens[1] = '\5';
			*tokens[0] = '\5';
		}
		else
			return (error_redir(tokens[1], control));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE << 8);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Opens a double output redirection (append).
 *
 * @details
 * If the token contains a double output redirection, it opens the file 
 * for appending and sets the output redirection in the command structure.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	open_output_double(char **tokens, t_command *cmd,
		char *control)
{
	if (tokens[0][0] == OUTPUT_REDIR && tokens[0][1] == OUTPUT_REDIR)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && tokens[1][0] != OUTPUT_REDIR
			&& tokens[1][0] != INPUT_REDIR && *tokens[1] != ENVP_VAR)
		{
			cmd->output_redirect
				= open(tokens[1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (cmd->output_redirect < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				if (!*tokens[1])
					ft_putstr_fd(": ", STDERR_FILENO);
				perror(tokens[1]);
			}
			*tokens[1] = '\5';
			*tokens[0] = '\5';
		}
		else
			return (error_redir(tokens[1], control));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE << 8);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Parses the output redirections in the tokens.
 *
 * @details
 * If the first token is not a quote, it tries to open a double output 
 * redirection and a simple output redirection.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	parse_output(char **tokens, t_command *cmd,
		char *control)
{
	int	error;

	error = 0;
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		error = open_output_double(tokens, cmd, control);
		if (error)
			return (error);
		error = open_output_simple(tokens, cmd, control);
		if (error)
			return (error);
	}
	return (error);
}

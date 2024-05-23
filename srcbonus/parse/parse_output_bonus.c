/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:35:45 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:43:14 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	open_output_simple(char **tokens, t_command *cmd,
		char *control)
{
	char	*redir;

	redir = ft_strchr(tokens[0], OUTPUT_REDIR);
	if (redir)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && *tokens[1] != '\0'
			&& tokens[1][0] != OUTPUT_REDIR && tokens[1][0] != INPUT_REDIR
			&& *tokens[1] != ENVP_VAR)
		{
			cmd->output_redirect = open(tokens[1], O_RDWR | O_CREAT, 0666);
			if (cmd->output_redirect < 0)
				perror(tokens[1]);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tokens[1], control));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	open_output_double(char **tokens, t_command *cmd,
		char *control)
{
	char	*redir;

	redir = ft_strnstr(tokens[0], "\4\4", ft_strlen(tokens[0]));
	if (redir)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && *tokens[1] != '\0'
			&& tokens[1][0] != OUTPUT_REDIR && tokens[1][0] != INPUT_REDIR
			&& *tokens[1] != ENVP_VAR)
		{
			cmd->output_redirect
				= open(tokens[1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (cmd->output_redirect < 0)
				perror(tokens[1]);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tokens[1], control));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_output(char **tokens, t_command *cmd,
		char *control)
{
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_output_double(tokens, cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_output_simple(tokens, cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

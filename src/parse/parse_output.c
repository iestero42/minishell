/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:35:45 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/02 11:17:14 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_simple(char **tokens, t_command *cmd,
		int pos, t_minishell *data)
{
	char	*redir;
	char	*tmp;

	redir = ft_strchr(tokens[0], '>');
	if (redir)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		tmp = trim_command(tokens[1], data->last_status_cmd);
		if (*tmp != '\0' && !ft_strchr(tmp, '>') && !ft_strchr(tmp, '<'))
		{
			cmd->output_redirect = open(tmp, O_RDWR | O_CREAT, 0666);
			if (cmd->input_redirect < 0)
				perror(tmp);
			free(tmp);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	open_output_double(char **tokens, t_command *cmd,
		int pos, t_minishell *data)
{
	char	*redir;
	char	*tmp;

	redir = ft_strnstr(tokens[0], ">>", ft_strlen(tokens[0]));
	if (redir)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		tmp = trim_command(tokens[1], data->last_status_cmd);
		if (*tmp != '\0' && !ft_strchr(tmp, '>') && !ft_strchr(tmp, '<'))
		{
			cmd->output_redirect = open(tmp, O_RDWR | O_CREAT | O_APPEND, 0666);
			if (cmd->input_redirect < 0)
				perror(tmp);
			free(tmp);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_output(char **tokens, t_command *cmd,
		int pos, t_minishell *data)
{
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_output_double(tokens, cmd, pos, data)== EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_output_simple(tokens, cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:35:45 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/08 10:19:13 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_simple(char *token, t_command *cmd, char *next_token)
{
	char	*redir;

	redir = ft_strchr(token, '>');
	while (redir != NULL)
	{
		if (redir && !ft_strnstr(redir, ">>", ft_strlen(redir)))
		{
			if (cmd->output_redirect > -1)
				close(cmd->output_redirect);
			if (*(redir++) != '\0' && *redir != '<')
				cmd->output_redirect = open(redir, O_RDWR | O_CREAT, 0666);
			else if (next_token != NULL && *redir != '<')
			{
				cmd->output_redirect = open(next_token,
						O_RDWR | O_CREAT, 0666);
				next_token = NULL;
			}
			else
				return (EXIT_FAILURE);
			*redir = '\0';
		}
		redir = ft_strchr(redir, '>');
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	open_output_double(char *token, t_command *cmd, char *next_token)
{
	char	*redir;

	redir = ft_strnstr(token, ">>", ft_strlen(token));
	if (redir)
	{
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (ft_strcmp(redir + 2, ""))
			cmd->output_redirect = open(redir + 2,
					O_RDWR | O_CREAT | O_APPEND, 0666);
		else if (next_token != NULL)
		{
			cmd->output_redirect = open(next_token,
					O_RDWR | O_CREAT | O_APPEND, 0666);
			next_token = NULL;
		}
		else
			return (EXIT_FAILURE);
		*redir = '\0';
	}
	if (cmd->output_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_output(char *token, t_command *cmd, char *nextToken)
{
	if (token[0] != '"' && token[0] != '\'')
	{
		if (open_output_double(token, cmd, nextToken) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_output_simple(token, cmd, nextToken) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

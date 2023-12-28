/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/28 11:42:34 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input_simple(char *token, t_command *cmd, char *nextToken)
{
	char	*redir;
	char	*filename;

	redir = ft_strchr(token, '<');
	if (redir && !ft_strnstr(token, "<<", ft_strlen(token)))
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		if (ft_strcmp(redir + 1, ""))
		{
			filename = redir + 1;
			cmd->input_redirect = open(filename, O_RDWR, 0666);
			return (EXIT_SUCCESS);
		}
		else if (nextToken != NULL)
		{
			cmd->input_redirect = open(nextToken, O_RDWR, 0666);
			return (EXIT_SUCCESS);
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	open_input_double(char *token, t_command *cmd, char *nextToken)
{
	char	*redir;
	char	*filename;

	redir = ft_strnstr(token, "<<", ft_strlen(token));
	if (redir)
	{
		if (cmd->input_redirect > -1)
		{
			close(cmd->output_redirect);
			unlink("here_doc");
		}
		if (ft_strcmp(redir + 2, ""))
		{
			filename = redir + 2;
			cmd->output_redirect = open(filename,
					O_RDWR | O_CREAT | O_APPEND, 0666);
			return (EXIT_SUCCESS);
		}
		else if (nextToken != NULL)
		{
			cmd->output_redirect = open(nextToken,
					O_RDWR | O_CREAT | O_APPEND, 0666);
			return (EXIT_SUCCESS);
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


static int	built_input(char *token, t_command *cmd, char *nextToken)
{
	
}

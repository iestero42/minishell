/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/27 11:58:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_simple(char *token, t_command *cmd, char *nextToken)
{
	char	*redir;
	char	*filename;

	redir = ft_strchr(token, '<');
	if (redir)
	{
		if (cmd->output_redirect)
			close(cmd->input_redirect);
		if (redir + 1 != '\0')
		{
			filename = redir + 1;
			cmd->output_redirect = open(filename,
					O_RDWR, 0666);
			return (EXIT_SUCCESS);
		}
		else if (nextToken != NULL)
		{
			cmd->output_redirect = open(nextToken,
					O_RDWR, 0666);
			return (EXIT_SUCCESS);
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	open_output_double(char *token, t_command *cmd, char *nextToken)
{
	char	*redir;
	char	*filename;

	redir = ft_strnstr(token, "<<", ft_strlen(token));
	if (redir)
	{
		if (cmd->output_redirect)
			close(cmd->output_redirect);
		if (redir + 2 != '\0')
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

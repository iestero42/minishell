/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/04 08:06:10 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_simple(char *token, t_command *cmd, char *next_token)
{
	char	*redir;

	redir = ft_strchr(token, '<');
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		if (next_token != NULL && ft_strcmp(next_token, "")
			&& !ft_strchr(next_token, '>') && !ft_strchr(next_token, '<'))
		{
			cmd->input_redirect = open(next_token, O_RDWR, 0666);
			*next_token = '\0';
			*token = '\0';
		}
		else
			return (EXIT_FAILURE);
	}
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param delimiter 
 * @return int 
 */
static int	write_here_doc(char *delimiter)
{
	char	*line;
	int		here_doc;

	line = readline(">");
	here_doc = open("here_doc", O_RDWR, O_CREAT, 0666);
	if (here_doc == -1)
		return (EXIT_FAILURE);
	while (ft_strcmp(line, delimiter))
	{
		ft_putstr_fd(line, here_doc);
		line = readline(">");
	}
	return (here_doc);
}

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_double(char *token, t_command *cmd, char *next_token)
{
	char	*redir;

	redir = ft_strnstr(token, "<<", ft_strlen(token));
	if (redir)
	{
		if (cmd->input_redirect > -1)
		{
			close(cmd->output_redirect);
			unlink("here_doc");
		}
		else if (next_token != NULL && !ft_strchr(next_token, '>')
			&& !ft_strchr(next_token, '<'))
		{
			cmd->input_redirect = write_here_doc(next_token);
			*next_token = '\0';
			*token = '\0';
		}
		else
			return (EXIT_FAILURE);
	}
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
int	built_input(char *token, t_command *cmd, char *next_token)
{
	if (token[0] != '"' && token[0] != '\'')
	{
		if (open_input_double(token, cmd, next_token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(token, cmd, next_token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

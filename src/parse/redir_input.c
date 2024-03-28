/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/28 10:47:50 by iestero-         ###   ########.fr       */
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
			cmd->input_redirect = open(next_token, O_RDONLY, 0644);
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
static int	write_here_doc(char *delimiter, char *filename)
{
	char	*line;
	int		here_doc;

	here_doc = open(filename, O_WRONLY | O_CREAT, 0644);
	if (here_doc == -1)
		return (EXIT_FAILURE);
	ft_putstr_fd(">", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
	{
		ft_putstr_fd(line, here_doc);
		free(line);
		ft_putstr_fd(">", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_doc);
	here_doc = open(filename, O_RDONLY);
	if (here_doc < 0)
		perror(filename);
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
			unlink(cmd->here_doc);
		}
		if (next_token != NULL && !ft_strchr(next_token, '>')
			&& !ft_strchr(next_token, '<'))
		{
			cmd->input_redirect = write_here_doc(next_token, cmd->here_doc);
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

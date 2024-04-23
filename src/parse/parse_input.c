/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 13:31:25 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_simple(char **tokens, t_command *cmd,
				int pos, t_minishell *data)
{
	char	*redir;
	char	**tmp;

	redir = ft_strchr(tokens[0], '<');
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		tmp = trim_command(tokens[1], data->last_status_cmd);
		if (tmp != NULL && **tmp != '\0' && tokens[1][0] != '<'
			&& tokens[1][0] != '>')
		{
			cmd->input_redirect = open(tmp[0], O_RDONLY, 0644);
			if (cmd->input_redirect < 0)
				perror(tmp[0]);
			free(tmp);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
	}
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	controller_heredoc(pid_t pid, int *fd, t_minishell *data)
{
	int	status;

	status = -1;
	close(fd[1]);
	while (1)
	{
		waitpid(pid, &status, WNOHANG);
		if (g_signal == 2)
		{
			close(fd[0]);
			data->status = STOPPED;
			kill(pid, SIGTERM);
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (status != -1)
			break ;
	}
}

/**
 * @brief 
 * 
 * @param delimiter 
 * @return int 
 */
static int	write_here_doc(char *delimiter, int last_status, t_minishell *data)
{
	char	*line;
	pid_t	pid;
	int		pipes[2];

	if (pipe(pipes) < 0)
		error_init("pipe", 1);
	pid = fork();
	if (pid < 0)
		error_init("fork", 1);
	if (pid == 0)
	{
		close(pipes[0]);
		line = readline_own();
		while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
		{
			line = parse_env_variable(line, last_status, '\0');
			ft_putstr_fd(line, pipes[1]);
			free(line);
			line = readline_own();
		}
		exit(0);
	}
	free(delimiter);
	controller_heredoc(pid, pipes, data);
	return (pipes[0]);
}

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_double(char **tokens, t_command *cmd,
				int pos, t_minishell *data)
{
	char	*redir;
	char	**tmp;

	redir = ft_strnstr(tokens[0], "<<", ft_strlen(tokens[0]));
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->output_redirect);
		tmp = trim_command(tokens[1], data->last_status_cmd);
		if (tmp != NULL && **tmp != '\0' && tokens[1][0] != '<'
			&& tokens[1][0] != '>')
		{
			cmd->input_redirect = write_here_doc(tmp[0],
					data->last_status_cmd, data);
			free(tmp);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
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
int	parse_input(char **tokens, t_command *cmd,
		int pos, t_minishell *data)
{
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_input_double(tokens, cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(tokens, cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

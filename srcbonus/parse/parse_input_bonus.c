/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:54:28 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
				char *control)
{
	char	*redir;

	redir = ft_strchr(tokens[0], INPUT_REDIR);
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		if (tokens[1] != NULL && *tokens[1] != '\0'
			&& tokens[1][0] != INPUT_REDIR && tokens[1][0] != OUTPUT_REDIR
			&& *tokens[1] != ENVP_VAR)
		{
			cmd->input_redirect = open(tokens[1], O_RDONLY, 0644);
			if (cmd->input_redirect < 0)
				perror(tokens[1]);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tokens[1], control));
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
static int	write_here_doc(char *delimiter, int last_status, t_minishell *data,
				int pipes[2])
{
	char	*line;
	char	*tmp;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_init("fork", 1);
	if (pid == 0)
	{
		close(pipes[0]);
		line = readline_own();
		while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
		{
			tmp = parse_env_variable(line, last_status, '\0');
			free(line);
			line = tmp;
			ft_putstr_fd(line, pipes[1]);
			free(line);
			line = readline_own();
		}
		free(line);
		exit(0);
	}
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
				char *control, t_minishell *data)
{
	char	*redir;
	int		pipes[2];

	redir = ft_strnstr(tokens[0], "\3\3", ft_strlen(tokens[0]));
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && *tokens[1] != '\0'
			&& tokens[1][0] != INPUT_REDIR && tokens[1][0] != OUTPUT_REDIR
			&& *tokens[1] != ENVP_VAR)
		{
			if (pipe(pipes) < 0)
				error_init("pipe", 1);
			cmd->input_redirect = write_here_doc(tokens[1],
					data->last_status_cmd, data, pipes);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tokens[1], control));
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
		char *control, t_minishell *data)
{
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_input_double(tokens, cmd, control, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(tokens, cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

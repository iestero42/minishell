/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/18 09:14:07 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_input_bonus.c
 * @brief Contains the functions for parsing input.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Opens a simple input redirection.
 *
 * @details
 * If the token contains an input redirection, it opens the file for reading
 * and sets the input redirection in the command structure.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	open_input_simple(char **tokens, t_command *cmd,
				char *control)
{
	if (tokens[0][0] == INPUT_REDIR)
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		if (tokens[1] != NULL && tokens[1][0] != INPUT_REDIR
			&& tokens[1][0] != OUTPUT_REDIR && *tokens[1] != ENVP_VAR)
		{
			cmd->input_redirect = open(tokens[1], O_RDONLY, 0644);
			if (cmd->input_redirect < 0)
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
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Controls the heredoc process.
 *
 * @details
 * Waits for the heredoc process to finish and handles signals.
 *
 * @param pid The process ID of the heredoc process.
 * @param fd The file descriptor of the heredoc.
 * @param data The minishell data.
 */
static int	controller_heredoc(pid_t pid, int *fd, t_minishell *data)
{
	int	status;

	status = -1;
	close(fd[1]);
	signal(SIGINT, signal_handler);
	waitpid(pid, &status, 0);
	if (status == 33280)
	{
		data->last_status_cmd = status;
		close(fd[0]);
		data->status = STOPPED;
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	return (fd[0]);
}

/**
 * @brief 
 * Writes a heredoc to a pipe.
 *
 * @details
 * Forks a new process, reads lines from the standard input until the 
 * delimiter is found, parses environment variables in the lines, and 
 * writes them to the pipe.
 *
 * @param delimiter The delimiter of the heredoc.
 * @param last_status The last status of the command.
 * @param data The minishell data.
 * @param pipes The pipes to write to.
 * @return The read end of the pipe.
 */
static int	write_here_doc(char *delimiter, int last_status,
				int pipes[2], t_minishell *data)
{
	char		*line;
	char		*tmp;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, signal_free_environ);
		close(pipes[0]);
		line = readline("> ");
		while (line != NULL && ft_strncmp(line, delimiter, ft_strlen(line)))
		{
			line = ft_strjoin(line, "\n");
			tmp = parse_env_variable(line, last_status, '\0');
			free(line);
			line = tmp;
			ft_putstr_fd(line, pipes[1]);
			free(line);
			line = readline("> ");
			data->n_line++;
		}
		check_err_heredoc(line, data->n_line, delimiter);
	}
	return (controller_heredoc(pid, pipes, data));
}

/**
 * @brief 
 * Opens a double input redirection (heredoc).
 *
 * @details
 * If the token contains a heredoc, it writes the heredoc to a pipe
 * and sets the input redirection in the command structure.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	open_input_double(char **tokens, t_command *cmd,
				char *control, t_minishell *data)
{
	int		pipes[2];

	if (tokens[0][0] == INPUT_REDIR && tokens[0][1] == INPUT_REDIR)
	{
		if (cmd->input_redirect > -1)
			close(cmd->output_redirect);
		if (tokens[1] != NULL && tokens[1][0] != INPUT_REDIR
			&& tokens[1][0] != OUTPUT_REDIR && *tokens[1] != ENVP_VAR)
		{
			if (pipe(pipes) < 0)
				error_init("pipe", 1);
			cmd->input_redirect = write_here_doc(tokens[1],
					data->last_status_cmd, pipes, data);
			*tokens[1] = '\5';
			*tokens[0] = '\5';
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
 * Parses the input redirections in the tokens.
 *
 * @details
 * If the first token is not a quote, it tries to open a double 
 * input redirection and a simple input redirection.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	parse_input(char **tokens, t_command *cmd,
		char *control, t_minishell *data)
{
	show_eof_symbol();
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_input_double(tokens, cmd, control, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(tokens, cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	hide_eof_symbol();
	return (EXIT_SUCCESS);
}

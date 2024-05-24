/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 14:51:45 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_input_bonus.c
 * @brief Contains the functions for parsing input.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

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
		line = readline_own("> ");
		while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
		{
			tmp = parse_env_variable(line, last_status, '\0');
			free(line);
			line = tmp;
			ft_putstr_fd(line, pipes[1]);
			free(line);
			line = readline_own("> ");
		}
		free(line);
		exit(0);
	}
	controller_heredoc(pid, pipes, data);
	return (pipes[0]);
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
	struct termios	term;

	show_eof_symbol(&term);
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_input_double(tokens, cmd, control, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(tokens, cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	hide_eof_symbol(&term);
	return (EXIT_SUCCESS);
}

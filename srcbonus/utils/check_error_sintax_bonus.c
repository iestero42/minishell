/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:27:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/10 12:58:37 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/**
 * @brief Appends a line token to the tokens array.
 *
 * @details This function reads a line from the given file descriptor using 
 * `get_next_line`, trims the newline and space characters from the line, and 
 * appends the trimmed line to the tokens array. This process is repeated until 
 * `get_next_line` returns NULL, indicating that there are no more lines to read.
 *
 * @param tokens The tokens array to append to.
 * @param fd The file descriptor to read from.
 * @return The updated tokens array.
 */
static char	**append_line_token(char **tokens, int fd)
{
	char		*line;
	char		*tmp;

	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_strtrim(line, "\n ");
		free(line);
		if (!tmp)
			error_init("malloc", 1);
		tokens = ft_append(tokens, tmp);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	return (tokens);
}

/**
 * @brief Reads a complete command from the user.
 *
 * @details This function reads a line from the user using `readline`,
 * trims the newline and space characters from the line, and splits 
 * the trimmed line into tokens. If the line is empty or NULL, 
 * an error message is printed and the program exits.
 *
 * @return The tokens array representing the command, or NULL 
 * if an error occurred.
 */
static char	**read_complete_command(void)
{
	char		*line;
	char		*tmp;
	extern char	**environ;
	char		**tokens;

	signal(SIGINT, signal_free_environ);
	line = readline("> ");
	double_free(environ);
	if (!line || *line == '\0')
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\nexit\n",
			STDERR_FILENO);
		exit(2);
	}
	tmp = ft_strtrim(line, "\n ");
	if (!tmp)
		error_init("malloc", 1);
	tokens = split_command(tmp);
	if (!tokens)
		error_init("malloc", 1);
	free(line);
	free(tmp);
	return (tokens);
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
static char	**monitor(pid_t pid, int *fd, char **tokens, t_minishell *data)
{
	int			status;
	extern char	**environ;

	status = -1;
	signal(SIGINT, signal_handler);
	close(fd[1]);
	while (status != 0)
	{
		waitpid(pid, &status, 0);
		if (status > 0)
		{
			data->last_status_cmd = status;
			double_free(tokens);
			if (status == 512)
			{
				double_free(environ);
				exit(2);
			}
			if ((status >> 8) == 130)
				return (NULL);
		}
	}
	signal(SIGINT, SIG_IGN);
	tokens = append_line_token(tokens, fd[0]);
	return (tokens);
}

/**
 * @brief Executes a command and captures its output.
 *
 * @details This function forks a new process to execute a command and captures
 * its output. The command is read using `read_complete_command`, and its output
 * is written to a pipe. The parent process waits for the child to finish and
 * reads the output from the pipe.
 *
 * @param command_line The command to execute.
 * @param data The shell data.
 * @return The output of the command, or NULL if the command was stopped.
 */
static char	**execute_and_capture_command(char **command_line,
	t_minishell *data)
{
	pid_t			pid;
	int				pipes[2];
	int				i;

	pipe(pipes);
	pid = fork();
	if (pid < 0)
		error_init("fork", 1);
	if (pid == 0)
	{
		close(pipes[0]);
		command_line = read_complete_command();
		i = -1;
		while (command_line[++i] != NULL)
		{
			ft_putstr_fd(command_line[i], pipes[1]);
			ft_putstr_fd("\n", pipes[1]);
		}
		exit(EXIT_SUCCESS);
	}
	command_line = monitor(pid, pipes, command_line, data);
	if (command_line == NULL)
		data->status = STOPPED;
	return (command_line);
}

/**
 * @brief 
 * Handles parenthesis errors.
 *
 * @details
 * This function iterates over the tokens and checks for an uneven number 
 * of open and closed parentheses, an open parenthesis that is not 
 * preceded by a '&' or '|', or a '&' or '|' that is not correctly placed.
 * If any of these errors are found, an error message is printed 
 * and EXIT_FAILURE is returned. If no errors
 * are found, EXIT_SUCCESS is returned.
 *
 * @param tokens An array of char pointers containing the input tokens.
 * @return Returns EXIT_FAILURE if a parenthesis error is found, and 
 * 	EXIT_SUCCESS otherwise.
 */
char	**check_err_sintax(char **tokens, t_minishell *data, int count)
{
	int	i;

	i = -1;
	while (data->status == RUNNING && tokens[++i] != NULL)
	{
		if (*tokens[i] == ')')
			count--;
		if (*tokens[i] == '(' && ++count && (i > 0
				&& *tokens[i - 1] != '&' && *tokens[i - 1] != '|'))
			return (print_estd(tokens, 1, i, data));
		if (count < 0 || (*tokens[i] == '(' && tokens[i + 1]
				&& *tokens[i + 1] == ')'))
			return (print_estd(tokens, 2, i, data));
		if ((*tokens[i] == '&' || *tokens[i] == '|') && i == 0)
			return (print_estd(tokens, 3, i, data));
		if ((*tokens[i] == ')' && tokens[i + 1] && (*tokens[i + 1] != '|'
					&& *tokens[i + 1] != '&')) || ((*tokens[i] == '&'
					|| *tokens[i] == '|') && tokens[i + 1]
				&& (*tokens[i + 1] == '&' || *tokens[i + 1] == '|')))
			return (print_estd(tokens, 4, i, data));
		if (!tokens[i + 1] && ((count > 0) || (count == 0
					&& (*tokens[i] == '&' || *tokens[i] == '|'))))
			tokens = execute_and_capture_command(tokens, data);
	}
	return (tokens);
}

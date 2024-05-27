/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:27:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/27 13:38:54 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

void sigint_handler(int sig)
{
    (void)sig;
    g_signal = 2;
}

static char **read_complete_command(void)
{
    char	*line;
    char    *tmp;
    char    **tokens;

	
	line = readline("> ");
	if (*line != '\0')
	{
		tmp = ft_strtrim(line, "\n ");
		if (!tmp)
			error_init("malloc", 1);
		tokens = split_command(tmp);
		if (!tokens)
			error_init("malloc", 1);
		free(line);
		free(tmp);
	}
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
static char	**controller_main(pid_t pid, int *fd, char **tokens)
{
	int		status;
	char	*line;
	char   	*tmp;

	status = -1;
	close(fd[1]);
	while (1)
	{
		waitpid(pid, &status, WNOHANG);
		if (g_signal == 2)
		{
			close(fd[0]);
			kill(pid, SIGTERM);
			ft_putstr_fd("\n", 1);
			double_free(tokens);
			return (NULL);
		}
		if (status != -1)
			break ;
	}
	line = get_next_line(fd[0]);
	while (line != NULL)
	{
		tmp = ft_strtrim(line, "\n ");
		free(line);
		if (!tmp)
			error_init("malloc", 1);
		tokens = ft_append(tokens, tmp);
		free(tmp);
		line = get_next_line(fd[0]);
	}
	close(fd[0]);
	return (tokens);
}

static char	**read_complete_command_main(char **command_line, t_minishell *data)
{
	pid_t			pid;
	struct termios	term;
	int				pipes[2];
	int				i;
	
	pipe(pipes);
	signal(SIGINT, sigint_handler);
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
	command_line = controller_main(pid, pipes, command_line);
	if (!command_line)
		data->status = STOPPED;
	signal(SIGINT, signal_handler_readline);
	return (command_line);
}

/**
 * @brief 
 * Handles parenthesis errors.
 *hide_eof_symbol(&term);
 * @details
 * This function iterates over the tokens and checks for an uneven number of open 
 * and closed parentheses, an open parenthesis that is not preceded by a '&' or '|', 
 * or a '&' or '|' that is not correctly placed.
 * If any of these errors are found, an error message is printed and EXIT_FAILURE 
 * is returned. If no errors
 * are found, EXIT_SUCCESS is returned.
 *
 * @param tokens An array of char pointers containing the input tokens.
 * @return Returns EXIT_FAILURE if a parenthesis error is found, and 
 * 	EXIT_SUCCESS otherwise.
 */
char	**check_err_sintax(char **tokens, t_minishell *data)
{
	int	i;
	int	count_parentheses;

	i = -1;
	count_parentheses = 0;
	while (data->status == RUNNING && tokens[++i] != NULL)
	{
		if (*tokens[i] == ')')
			count_parentheses--;
		if (*tokens[i] == '(' && ++count_parentheses
			&& (i > 0 && *tokens[i - 1] !=  '&' && *tokens[i - 1] != '|'))
			return (print_estd(tokens, 1, i));
		if (count_parentheses < 0 || (*tokens[i] == '('
			&& tokens[i + 1] != NULL && *tokens[i + 1] == ')'))
			return (print_estd(tokens, 2, i));
		if (((*tokens[i] == '&' || *tokens[i] == '|') && (i == 0
			|| (tokens[i + 1] != NULL && (*tokens[i + 1] == '&'
			|| *tokens[i + 1] == '|')))) || (*tokens[i] == ')'
			&& tokens[i + 1] != NULL && (*tokens[i + 1] != '|'
			&& *tokens[i + 1] != '&')))
			return (print_estd(tokens, 3, i));
		if (tokens[i + 1] == NULL && ((count_parentheses > 0) || (count_parentheses == 0
			&& (*tokens[i] == '&' || *tokens[i] == '|'))))
			tokens = read_complete_command_main(tokens, data);
	}
	return (tokens);
}
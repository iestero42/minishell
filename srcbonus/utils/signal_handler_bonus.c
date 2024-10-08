/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:28 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/16 21:15:38 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_handler_bonus.c
 * @brief Contains functions for handling signals.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Handles signals during readline.
 *
 * @details
 * If the signal is SIGINT, it prints a newline, sets a new line in 
 * readline, replaces the line with an empty string, redisplays the line, 
 * and sets the global signal to 2.
 *
 * @param signum The signal number.
 */
void	signal_handler_readline(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

/**
 * @brief 
 * Handles signals received by the process.
 * 
 * @details
 * This function is designed to handle signals sent to the process. When a
 * signal is received, it simply prints "^C" to the standard output. This is
 * typically used to handle SIGINT (Ctrl+C) signals in a custom way, but it
 * can be adapted for other signals as well.
 * 
 * @param sig The signal number received.
 */
void	signal_handler(int sig)
{
	(void) sig;
	printf("^C\n");
}

/**
 * @brief
 * Frees environment variables and exits on SIGINT.
 * 
 * @details
 * This function is called when a signal is received by the process. It first
 * frees the environment variables stored in the global 'environ' variable by
 * calling 'double_free'. If the received signal is SIGINT (signal number for
 * interrupt signal, typically generated by pressing Ctrl+C), the process
 * exits with the status code 130, which is the conventional exit status for
 * processes terminated by SIGINT.
 * 
 * @param signum The signal number received.
 */
void	signal_free_environ(int signum)
{
	extern char	**environ;

	double_free(environ);
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGQUIT)
		exit(131);
}

/**
 * @brief 
 * Controls the execution of a process.
 *
 * @details
 * Waits for the process to change state. If the process has changed state, 
 * it increments the total. Sends a signal to the process if necessary.
 * If the total is 1, it sets the status to STOPPED.
 * If the global signal is 2 or 3, it prints a newline to the standard output.
 *
 * @param data The shell data structure.
 * @param pid The process ID.
 * @return The status of the process.
 */
int	controller(t_minishell *data, pid_t *pid)
{
	int				status_cmd;

	status_cmd = -1;
	signal(SIGINT, SIG_IGN);
	waitpid(*pid, &status_cmd, 0);
	if (WIFSIGNALED(status_cmd))
	{
		if (WTERMSIG(status_cmd) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			return (131 << 8);
		}
	}
	if (status_cmd == 2)
	{
		ft_putstr_fd("\n", data->std_fileno[0]);
		return (130 << 8);
	}
	return (status_cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:28 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/05 10:04:07 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_handler_bonus.c
 * @brief Contains functions for handling signals.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

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
		g_signal = 2;
	}
}

/**
 * @brief 
 * Handles signals.
 *
 * @details
 * If the signal is SIGINT, it sets the global signal to 2.
 * If the signal is SIGTERM, it frees the environment variables 
 * and sets the global signal to 3.
 *
 * @param signum The signal number.
 */
void	signal_handler(int signum)
{
	extern char	**environ;

	if (signum == SIGINT)
	{
		g_signal = 2;
	}
	if (signum == SIGTERM)
	{
		double_free(environ);
		g_signal = 3;
	}
}

void	sigint_handler(int sig)
{
    (void)sig;
	printf("^C\n");
}

void	signal_free_environ(int signum)
{
	extern char	**environ;
	
	if (signum == SIGINT)
		double_free(environ);
	exit(EXIT_FAILURE);
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
	int				result;
	int				total;
	int				status;

	total = 0;
	status = RUNNING;
	status_cmd = -1;
	while (status != STOPPED)
	{
		result = 0;
		result = waitpid(*pid, &status_cmd, WNOHANG);
		if (result > 0)
			total++;
		if (g_signal == 2)
		{
			kill(*pid, SIGTERM);
			status_cmd = (130 << 8);
		}		
		if (total == 1 || status_cmd != -1)
			status = STOPPED;
	}
	if (g_signal == 2 || g_signal == 3)
		ft_putstr_fd("\n", data->std_fileno[0]);
	return (status_cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:28 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 13:34:45 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

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

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2; 
	}
}

static void	signal_use(t_minishell *data, pid_t *pid)
{
	int	i;

	if (g_signal == 2)
	{
		i = -1;
		while (++i < data->n_commands)
			kill(pid[i], SIGTERM);
	}
}


void	controller(t_minishell *data, pid_t *pid)
{
	int				i;
	int				result;
	int				total;
	int				status;
	struct termios	term;

	total = 0;
	status = RUNNING;
	while (status != STOPPED)
	{
		i = -1;
		while (++i < data->n_commands)
		{
			result = 0;
			result = waitpid(pid[i], &data->last_status_cmd, WNOHANG);
			if (result > 0)
				total++;
		}
		signal_use(data, pid);
		if (total == data->n_commands)
			status = STOPPED;
	}
	if (g_signal == 2)
		printf("\n");
	hide_eof_symbol(&term);
}

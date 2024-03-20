/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:28 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/20 11:03:26 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_use(t_minishell *data, pid_t *pid)
{
	int	i;

	if (g_signal == 2 || g_signal == 1)
	{
		i = 0;
		while (i < data->n_comands)
			kill(pid[i], SIGTERM);
		data->status = STOPPED;
		if (g_signal == 1)
		{
			full_free(data);
			free(pid);
			exit(0);
		}
	}
}


void	controller(t_minishell *data, pid_t *pid)
{
	int	i;
	int	result;
	int	total;

	data->last_status_cmd = 0;
	total = 0;
	while (data->status != STOPPED)
	{
		i = -1;
		while (++i < data->n_comands)
		{
			result = 0;
			result = waitpid(pid[i], &data->last_status_cmd, WNOHANG);
			if (result > 0)
				total++;
		}
		signal_use(data, pid);
		if (total == data->n_comands)
			data->status = STOPPED;
	}
}

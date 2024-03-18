/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:28 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:09:27 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_signal = 2;
	}
	else if (signum == SIGQUIT)
		g_signal = 3;
	else if (signum == SIGTERM)
	{
		ft_putstr_fd("exit", 2);
		g_signal = 1;
	}
}

void	controller(t_minishell *data, pid_t *pid)
{
	int	i;

	data->last_status_cmd = 0;
	while (data->status != STOPPED)
	{
		i = -1;
		while (++i < data->n_comands)
			waitpid(pid[i], &data->last_status_cmd, WNOHANG);
		if (g_signal == 2 || g_signal == 1)
		{
			i = 0;
			while (i < data->n_comands)
				kill(pid[i], SIGTERM);
			full_free(data);
			data->status = STOPPED;
			if (g_signal == 1)
				exit(0);
		}
	}
}

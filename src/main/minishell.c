/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 10:46:09 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	open_pipes(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->n_comands - 1)
	{
		if (pipe(data->pipes + 2 * i) < 0)
			error_init("pipe", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	minishell(t_minishell *data)
{
	pid_t	*pids;
	int		i;

	if (data->n_comands > 1)
	{
		data->pipes = (int *) malloc(sizeof(int) * 2 * (data->n_comands - 1));
		if (!data->pipes)
			error_init("malloc", 1);
		open_pipes(data);
		pids = (pid_t *) malloc(sizeof(pid_t) * data->n_comands);
		if (!pids)
			error_init("malloc", 1);
		i = -1;
		while (++i < data->n_comands)
			pids[i] = create_process(&data->comand_split[i], data->pipes, i,
					data);
		close_pipes(data);
		free(data->pipes);
		controller(data, pids);
		free(pids);
	}
	else
		execute_command(&data->comand_split[0], data);
	full_free(data);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_minishell	data;
	char		*line;

	init(&data);
	while (data.status != STOPPED)
	{
		signal(SIGINT, signal_handler_readline);
		line = readline_main();
		if (line == NULL)
		{
			print_exit();
			break ;
		}
		if (*line != '\0')
		{
			add_history(line);
			signal(SIGINT, signal_handler);
			if (parse_data(line, &data) == EXIT_SUCCESS)
				minishell(&data);
		}
		free(line);
	}
	deinit(&data);
	return (0);
}
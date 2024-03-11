/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/11 11:49:45 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_title(void)
{
	printf(LINE_1, BLUE, RESET);
	printf(LINE_2, BLUE, RESET, BLUE, RESET);
	printf(LINE_3, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_4, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_5, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_6, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_7, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_8, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_9, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_10, BLUE, RESET, BLUE, RESET);
	printf(LINE_11, BLUE, RESET);
}

static void	init_data(t_minishell *data, char **env)
{
	data->status = RUNNING;
	data->std_fileno[1] = dup(STDOUT_FILENO);
	data->std_fileno[0] = dup(STDIN_FILENO);
	data->cmd_list[0] = "echo";
	data->cmd_list[1] = "cd";
	data->cmd_list[2] = "pwd";
	data->cmd_list[3] = "export";
	data->cmd_list[4] = "unset";
	data->cmd_list[5] = "env";
	data->cmd_list[6] = "exit";
	data->env = env;
}

static int	open_pipes(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->n_comands - 1)
	{
		if (pipe(data->pipes + 2 * i) < 0)
			return (EXIT_FAILURE);
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
		data->pipes = (int *) malloc(sizeof(int) * (data->n_comands - 1));
		open_pipes(data);
		pids = (pid_t *) malloc(sizeof(pid_t) * data->n_comands);
		if (!pids)
			return (EXIT_FAILURE);
		i = -1;
		while (++i < data->n_comands)
			pids[i] = create_process(data->comand_split[i], data->pipes, i,
					data);
	}
	else
		execute_command(data->comand_split[0], data);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	data;

	if (argc != 1 || argv == NULL)
		return (-1);
	show_title();
	init_data(&data, env);
	while (data.status != STOPPED)
	{
		parse_data("echo hola> como >>adios", &data);
		minishell(&data);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/04 09:39:16 by iestero-         ###   ########.fr       */
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

static void	init_data(t_minishell *data)
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
}

int	open_pipes(t_minishell *pipex_args)
{
	int	i;

	i = 0;
	while (i < pipex_args->pipes)
	{
		if (pipe(pipex_args->end + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	minishell(t_minishell *data)
{
	data->pipes = (int *) malloc(sizeof(int) * (data->n_comands - 1));
	
}

int	main(void)
{
	t_minishell	data;

	show_title();
	init_data(&data);
	while (data.status != STOPPED)
	{
		init_data(&data);
		parse_data("echo hola> como >>adios", &data);
		minishell(&data);
	}
	return (0);
}

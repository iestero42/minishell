/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 10:06:48 by iestero-         ###   ########.fr       */
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

static int	minishell(void)
{
	return 1;
}

int	main(void)
{
	t_minishell	data;
	pid_t		pid;

	show_title();
	init_data(&data);
	while (data.status != STOPPED)
	{
		pid = fork();
		if (pid == 0)
		{
			init_data(&data);
			parse_data(readline(MINISHELL_ENTRY), &data);
			minishell();
			exit(0);
		}
		wait(NULL);
	}
	return (0);
}

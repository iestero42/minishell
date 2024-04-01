/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 09:55:14 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	show_title(void)
{
	printf(LINE_1, BLUE, RESET);
	printf(LINE_2, BLUE, RESET, BLUE, RESET);
	printf(LINE_3, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_4, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_5, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_6, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_7, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_8, BLUE, RESET);
}

static void	init_data(t_minishell *data, char **env)
{
	show_title();
	data->status = RUNNING;
	data->std_fileno[1] = dup(STDOUT_FILENO);
	if (data->std_fileno[1] < 0)
		error_init("stdout");
	data->std_fileno[0] = dup(STDIN_FILENO);
	if (data->std_fileno[0] < 0)
		error_init("stdin");
	data->cmd_list[0] = "echo";
	data->cmd_list[1] = "cd";
	data->cmd_list[2] = "pwd";
	data->cmd_list[3] = "export";
	data->cmd_list[4] = "unset";
	data->cmd_list[5] = "env";
	data->cmd_list[6] = "exit";
	data->cmd_list[7] = NULL;
	data->env = ft_dstrdup((const char **)env);
	if (data->env == NULL)
		error_init("ft_dstrdup");
	if (tcgetattr(STDIN_FILENO, &data->original_term) == -1)
		error_init("tcgetattr");
	configurations();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	open_pipes(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->n_comands - 1)
	{
		if (pipe(data->pipes + 2 * i) < 0)
			error_init("pipe");
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
			error_init("malloc");
		open_pipes(data);
		pids = (pid_t *) malloc(sizeof(pid_t) * data->n_comands);
		if (!pids)
			error_init("malloc");
		i = -1;
		while (++i < data->n_comands)
			pids[i] = create_process(&data->comand_split[i], data->pipes, i,
					data);
		close_pipes(data);
		controller(data, pids);
		free(pids);
	}
	else
		execute_command(&data->comand_split[0], data);
	full_free(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	data;
	char		*line;

	if (argc != 1 || argv == NULL)
		return (-1);
	init_data(&data, env);
	while (data.status != STOPPED)
	{
		line = readline("minishell~$ ");
		if (line == NULL)
		{
			print_exit();
			break ;
		}
		if (*line != '\0')
		{
			add_history(line);
			parse_data(line, &data);
			minishell(&data);
			free(line);
		}
	}
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &data.original_term);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:23:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:24:03 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	childs(int read, int write)
{
	if (dup2(read, 0) < 0
		|| dup2(write, 1) < 0)
	{
		perror("Error");
		exit(127);
	}
}

pid_t	create_process(t_command cmd, int *pipes, int pos, t_minishell *data)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		perror("fork");
	else if (child == 0)
	{
		if (cmd.input_redirect > -1 && cmd.output_redirect > -1)
			childs(cmd.input_redirect, cmd.output_redirect);
		else if (cmd.input_redirect < 0 && cmd.output_redirect > -1 && pos > 0)
			childs(pipes[2 * (pos - 1)], cmd.output_redirect);
		else if (cmd.input_redirect > -1 && cmd.output_redirect < 0)
			childs(cmd.input_redirect, pipes[pos * 2 + 1]);
		else if (pos == 0)
			childs(data->std_fileno[0], pipes[pos * 2 + 1]);
		else if (pos == data->n_comands - 1)
			childs(pipes[2 * (pos - 1)], data->std_fileno[1]);
		else
			childs(pipes[2 * (pos - 1)], pipes[pos * 2 + 1]);
		close_pipes(pipes);
		exec_command(cmd, data->env);
		full_free();
		exit(0);
	}
	return (child);
}

int	execute_command(t_command cmd, t_minishell *data)
{
	if (cmd.input_redirect > -1 && cmd.output_redirect > -1)
		childs(cmd.input_redirect, cmd.output_redirect);
	else if (cmd.input_redirect < 0 && cmd.output_redirect > -1)
		childs(data->std_fileno[0], cmd.output_redirect);
	else if (cmd.input_redirect > -1 && cmd.output_redirect < 0)
		childs(cmd.input_redirect, data->std_fileno[1]);
	else
		childs(data->std_fileno[0], data->std_fileno[1]);
	exec_command_special(cmd, data->env, &data);
	full_free();
}

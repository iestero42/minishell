/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:23:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/09 14:41:35 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dupping(int fd, int mode)
{
	if (dup2(fd, mode) < 0)
	{
		perror("dup");
		exit(1);
	}
}

static void	child_read(int fd, int *pipes, int pos)
{
	if (fd > -1)
		dupping(fd, STDIN_FILENO);
	else if (fd < 0 && pos > 0)
		dupping(pipes[2 * (pos - 1)], STDIN_FILENO);
}

static void	child_write(int fd, int *pipes, int pos, int n_commands)
{
	if (fd > -1)
		dupping(fd, STDOUT_FILENO);
	else if (fd < 0 && pos > -1 && pos < n_commands - 1)
		dupping(pipes[pos * 2 + 1], STDOUT_FILENO);
}

pid_t	create_process(t_command *cmd, int *pipes, int pos, t_minishell *data)
{
	pid_t			child;
	struct termios	term;
	extern char		**environ;

	child = fork();
	if (child < 0)
		error_init("fork", 1);
	else if (child == 0)
	{
		show_eof_symbol(&term);
		child_write(cmd->output_redirect, pipes, pos, data->n_commands);
		child_read(cmd->input_redirect, pipes, pos);
		close_pipes(data);
		exec_command(cmd);
		if (data->access_environ == 1)
			double_free(environ);
		exit(0);
	}
	return (child);
}

int	execute_command(t_command *cmd, t_minishell *data)
{
	if (cmd->input_redirect > -1 && cmd->output_redirect > -1)
	{
		dupping(cmd->input_redirect, STDIN_FILENO);
		dupping(cmd->output_redirect, STDOUT_FILENO);
	}
	else if (cmd->input_redirect < 0 && cmd->output_redirect > -1)
	{
		dupping(data->std_fileno[0], STDIN_FILENO);
		dupping(cmd->output_redirect, STDOUT_FILENO);
	}
	else if (cmd->input_redirect > -1 && cmd->output_redirect < 0)
	{
		dupping(cmd->input_redirect, STDIN_FILENO);
		dupping(data->std_fileno[1], STDOUT_FILENO);
	}
	exec_command_special(cmd, data);
	return (EXIT_SUCCESS);
}

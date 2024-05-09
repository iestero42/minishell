/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/09 14:44:50 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins(t_command cmd)
{
	if (cmd.type == ECHO_COMMAND)
		return (built_echo(cmd.args));
	else if (cmd.type == CD_COMMAND)
		return (built_cd(cmd.args));
	else if (cmd.type == PWD_COMMAND)
		return (built_pwd());
	else if (cmd.type == EXPORT_COMMAND)
		return (built_export(cmd.args));
	else if (cmd.type == UNSET_COMMAND)
		return (built_unset(cmd.args));
	else if (cmd.type == ENV_COMMAND)
		return (built_env());
	else if (cmd.type == EXIT_COMMAND)
		return (built_exit(cmd.args));
	return (EXIT_SUCCESS);
}

void	exec_command(t_command *cmd)
{
	extern char		**environ;

	if (cmd->type == PATH_COMMAND)
	{
		if (execve(cmd->name, cmd->args, environ) < 0)
			error_init("execve", 127);
		exit(0);
	}
	else if (cmd->type > 0)
	{
		if (builtins(*cmd) < 0)
		{
			double_free(environ);
			exit(127);
		}
	}
	else if (cmd->type == ERROR_COMMAND)
	{
		double_free(environ);
		exit(127);
	}
}

void	exec_command_special(t_command *cmd, t_minishell *data)
{
	pid_t			pid;
	extern char		**environ;
	struct termios	term;

	if (cmd->type == PATH_COMMAND)
	{
		pid = fork();
		if (pid < 0)
			error_init("fork", 1);
		if (pid == 0)
		{
			show_eof_symbol(&term);
			if (execve(cmd->name, cmd->args, environ) < 0)
				error_init("execve", 127);
			exit(0);
		}
		controller(data, &pid);
	}
	else if (cmd->type > 0)
	{
		if (builtins(*cmd) < 0)
			data->last_status_cmd = 127;
	}
	else if (cmd->type == ERROR_COMMAND)
		data->last_status_cmd = 127;
}

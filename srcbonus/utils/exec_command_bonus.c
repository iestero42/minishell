/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:20:21 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

int	exec_command_special(t_command *cmd, t_minishell *data)
{
	pid_t			pid;
	extern char		**environ;
	if (cmd->type == PATH_COMMAND)
	{
		pid = fork();
		if (pid < 0)
			error_init("fork", 1);
		if (pid == 0)
		{
			if (execve(cmd->name, cmd->args, environ) < 0)
				error_init("execve", 2);
			exit(0);
		}
		controller(data, &pid);
	}
	else if (cmd->type > 0)
	{
		if (builtins(*cmd) > 0)
			return (2);
	}
	else if (cmd->type == ERROR_COMMAND)
		return (127);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/19 09:59:05 by iestero-         ###   ########.fr       */
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

void	exec_command(t_command cmd, char **env)
{
	if (cmd.type == PATH_COMMAND)
	{
		if (execve(cmd.name, cmd.args, env) < 0)
		{
			perror("Error");
			exit(127);
		}
	}
	else
	{
		if (builtins(cmd) < 0)
		{
			perror("Error");
			exit(127);
		}
	}
}

void	exec_command_special(t_command cmd, char **env, t_minishell *data)
{
	pid_t	pid;

	if (cmd.type == PATH_COMMAND)
	{
		pid = fork();
		if (pid < 0)
			return (perror("exec_command"));
		if (pid == 0)
		{
			if (execve(cmd.name, cmd.args, env) < 0)
			{
				perror("Error");
				exit(127);
			}
			exit(0);
		}
		controller(data, &pid);
	}
	else
	{
		if (builtins(cmd) < 0)
			perror("Error");
	}
}

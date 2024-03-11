/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/11 11:39:54 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins(t_command cmd, char **env)
{
	if (cmd.type == ECHO_COMMAND)
		built_echo();
	else if (cmd.type == CD_COMMAND)
		built_cd();
	else if (cmd.type == PWD_COMMAND)
		built_pwd();
	else if (cmd.type == EXPORT_COMMAND)
		built_export();
	else if (cmd.type == UNSET_COMMAND)
		built_unset();
	else if (cmd.type == ENV_COMMAND)
		built_env();
	else if (cmd.type == EXIT_COMMAND)
		built_exit();
}

void	exec_command(t_command cmd, char **env)
{
	if (cmd.type == PATH_COMMAND)
	{
		if (execve(cmd.name, cmd.args, env) < 0)
		{
			child_free(cmd);
			perror("Error");
			exit(127);
		}
	}
	else
	{
		if (builtins(cmd, env) < 0)
		{
			child_free(cmd);
			perror("Error");
			exit(127);
		}
	}
	child_free(cmd);
}

void	exec_command_special(t_command cmd, char **env)
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
				child_free(cmd);
				perror("Error");
				exit(127);
			}
			exit(0);
		}
	}
	else
	{
		if (builtins(cmd, env) < 0)
			perror("Error");
	}
}

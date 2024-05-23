/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 14:46:29 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	dupping(int fd, int mode)
{
	if (dup2(fd, mode) < 0)
	{
		perror("dup");
		exit(1);
	}
}

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

static int	execute_command_logic(t_command *cmd, t_minishell *data)
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
		return (controller(data, &pid));
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

int	exec_command(t_command *cmd, t_minishell *data)
{
	struct termios	term;
	int				result;

	if (cmd->input_redirect < 0)
		show_eof_symbol(&term);
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
	result = execute_command_logic(cmd, data);
	if (cmd->input_redirect < 0)
		hide_eof_symbol(&term);
	return (result);
}

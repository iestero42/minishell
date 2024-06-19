/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/19 13:52:18 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_command_bonus.c
 * @brief Contains functions for executing commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Executes a builtin command.
 *
 * @details
 * Executes the specified builtin command and returns its exit status.
 *
 * @param cmd The command to execute.
 * @return The exit status of the command.
 */
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

static int	print_error_aux(struct stat path_stat, char *cmd)
{
	if (access(cmd, X_OK) != 0 && S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (126);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (127);
}

/**
 * @brief 
 * Prints an error message and returns EXIT_FAILURE.
 *
 * @param cmd The command that was not found.
 * @return Always returns EXIT_FAILURE.
 */
static int	print_error(char *cmd, int type)
{
	char		*path;
	struct stat	path_stat;

	if (type == ERROR_CMD_NAME)
	{
		path_stat.st_mode = 0;
		stat(cmd, &path_stat);
		path = getenv("PATH");
		if (!path || !*path || (ft_strchr(cmd, '/')
				&& (!path_stat.st_mode || !S_ISREG(path_stat.st_mode))))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
				return (126 << 8);
			}
			else
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else
			return (print_error_aux(path_stat, cmd) << 8);
	}
	return (type);
}

/**
 * @brief 
 * Executes a command.
 *
 * @details
 * Executes the specified command and returns its exit status.
 * If the command is a path command, it forks a new process and 
 * executes the command in the child process.
 * If the command is a builtin command, it executes the command 
 * in the current process.
 * If the command is an error command, it returns 127.
 *
 * @param cmd The command to execute.
 * @param data The shell data structure.
 * @return The exit status of the command.
 */
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
			signal(SIGQUIT, signal_free_environ);
			if (execve(cmd->name, cmd->args, environ) < 0)
			{
				double_free(environ);
				exit((print_error(cmd->name, ERROR_CMD_NAME) >> 8) & 0xFF);
			}
		}
		return (controller(data, &pid));
	}
	else if (cmd->type > 0 && cmd->type < 8)
		return (builtins(*cmd));
	else if (cmd->type)
		return (print_error(cmd->name, cmd->type));
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Executes a command with redirection.
 *
 * @details
 * Executes the specified command with input and output redirection.
 * If the command has input and output redirection, it duplicates 
 * the input and output file descriptors.
 * If the command has only output redirection, it duplicates the standard 
 * input and output file descriptors.
 * If the command has only input redirection, it duplicates the input 
 * file descriptor and the standard output file descriptor.
 * After executing the command, it hides the EOF symbol if the command has input 
 * redirection.
 *
 * @param cmd The command to execute.
 * @param data The shell data structure.
 * @return The exit status of the command.
 */
int	exec_command(t_command *cmd, t_minishell *data)
{
	int				result;

	if (cmd->input_redirect < 0)
		show_eof_symbol();
	if (cmd->output_redirect > -1)
		dupping(cmd->output_redirect, STDOUT_FILENO);
	if (cmd->input_redirect > -1)
		dupping(cmd->input_redirect, STDIN_FILENO);
	result = execute_command_logic(cmd, data);
	if (cmd->input_redirect < 0)
		hide_eof_symbol();
	return (result);
}

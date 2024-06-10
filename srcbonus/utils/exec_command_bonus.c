/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:15:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/10 09:53:51 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_command_bonus.c
 * @brief Contains functions for executing commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Duplicates a file descriptor.
 *
 * @details
 * Duplicates the specified file descriptor to the specified mode.
 * If an error occurs, it prints an error message and exits the program.
 *
 * @param fd The file descriptor to duplicate.
 * @param mode The mode to duplicate to.
 */
static void	dupping(int fd, int mode)
{
	if (dup2(fd, mode) < 0)
	{
		perror("dup");
		exit(1);
	}
}

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

/**
 * @brief 
 * Prints an error message and returns EXIT_FAILURE.
 *
 * @param cmd The command that was not found.
 * @return Always returns EXIT_FAILURE.
 */
static void	print_error(char *cmd, int type)
{
	char	*path;

	if (type == ERROR_CMD_NAME)
	{
		path = getenv("PATH");
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
	}
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
			if (execve(cmd->name, cmd->args, environ) < 0)
				error_init("execve", 2);
			exit(EXIT_SUCCESS);
		}
		return (controller(data, &pid));
	}
	else if (cmd->type > 0 && cmd->type < 8)
		return (builtins(*cmd));
	else if (cmd->type == ERROR_CMD_NAME || cmd->type == ERROR_REDIR)
	{
		print_error(cmd->name, cmd->type);
		return (cmd->type);
	}
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
		hide_eof_symbol();
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_minishell_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:23:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:29:59 by yunlovex         ###   ########.fr       */
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

static void	child_read(int fd, int *pipes)
{
	if (fd > -1)
		dupping(fd, STDIN_FILENO);
	else if (fd < 0)
		dupping(pipes[0], STDIN_FILENO);
}

static void	child_write(int fd, int *pipes)
{
	if (fd > -1)
		dupping(fd, STDOUT_FILENO);
	else if (fd < 0)
		dupping(pipes[1], STDOUT_FILENO);
}

/*pid_t	proc_minishell(t_minishell *data)
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
		child_write(cmd->output_redirect, pipes, pos, data->n_comands);
		child_read(cmd->input_redirect, pipes, pos);
		close_pipes(data);
		exec_command(cmd);
		if (data->access_environ == 1)
			double_free(environ);
		exit(0);
	}
	return (child);
}*/

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
	result = exec_command_special(cmd, data);
	if (cmd->input_redirect < 0)
		hide_eof_symbol(&term);
	return (result);
}

int	proc_minishell(t_minishell *data, t_tree *tree)
{
	pid_t 		child;
	pid_t		child2;
	int			result;
	extern char	**environ;

	result = -1;
	if (tree->left != NULL && tree->right != NULL)
	{
		if (tree->number == PIPE)
		{
			open_pipes(data);
			child = fork();
			if (child < 0)
				error_init("fork", 1);
			if (child == 0)
			{
				child_write(-1, data->pipes);
				close_pipes(data);
				result = proc_minishell(data, tree->left);
				double_free(environ);
				exit(result);
			}
			child2 = fork();
			if (child2 < 0)
				error_init("fork", 1);
			if (child2 == 0)
			{
				child_read(-1, data->pipes);
				close_pipes(data);
				result = proc_minishell(data, tree->right);
				double_free(environ);
				exit(result);
			}
			close_pipes(data);
			waitpid(child, &result, 0);
			waitpid(child2, &result, 0);
			return (result);
		}
		
		result = proc_minishell(data, tree->left);
		if ((tree->number == SEMICOLON && result > EXIT_SUCCESS)
			|| (tree->number == AND && result == EXIT_SUCCESS))
			result = proc_minishell(data, tree->right);
	}
	else
		result = exec_command(tree->content, data);
	return (result);
}

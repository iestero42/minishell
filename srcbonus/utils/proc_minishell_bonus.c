/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_minishell_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:23:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 14:50:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	open_pipes(t_minishell *data)
{
	if (pipe(data->pipes) < 0)
		error_init("pipe", 1);
	return (EXIT_SUCCESS);
}

static void	child_read(int fd, int *pipes)
{
	if (fd > -1)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup");
			exit(1);
		}
	}
	else if (fd < 0)
	{
		if (dup2(pipes[0], STDIN_FILENO) < 0)
		{
			perror("dup");
			exit(1);
		}
	}
}

static void	child_write(int fd, int *pipes)
{
	if (fd > -1)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup");
			exit(1);
		}
	}
	else if (fd < 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
		{
			perror("dup");
			exit(1);
		}
	}
}

static int	proc_childs(t_minishell *data, t_tree *tree, pid_t *ch, int mode)
{
	int			result;
	extern char	**environ;

	result = -1;
	*ch = fork();
	if (*ch < 0)
		error_init("fork", 1);
	if (*ch == 0)
	{
		if (mode == 0)
			child_write(-1, data->pipes);
		else if (mode == 1)
			child_read(-1, data->pipes);
		close_pipes(data);
		if (mode == 0)
			result = proc_minishell(data, tree->left);
		else if (mode == 1)
			result = proc_minishell(data, tree->right);
		double_free(environ);
		exit(result);
	}
	return (result);
}

int	proc_minishell(t_minishell *data, t_tree *tree)
{
	pid_t		child;
	pid_t		child2;
	int			result;

	result = -1;
	if (tree->left != NULL && tree->right != NULL)
	{
		if (tree->number == PIPE)
		{
			open_pipes(data);
			result = proc_childs(data, tree, &child, 0);
			result = proc_childs(data, tree, &child2, 1);
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

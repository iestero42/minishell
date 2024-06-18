/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:23:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/18 18:50:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file proc_minishell_bonus.c
 * @brief Contains functions for processing the minishell.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Opens the pipe file descriptors.
 *
 * @details
 * If an error occurs, it prints an error message and exits the program.
 *
 * @param data The shell data structure.
 * @return EXIT_SUCCESS.
 */
static int	open_pipes(t_minishell *data)
{
	if (pipe(data->pipes) < 0)
		error_init("pipe", 1);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Duplicates the standard input file descriptor in the child process.
 *
 * @details
 * If the file descriptor is greater than -1, it duplicates 
 * the file descriptor to the standard input.
 * If the file descriptor is less than 0, it duplicates the read 
 * end of the pipe to the standard input.
 *
 * @param fd The file descriptor.
 * @param pipes The pipe file descriptors.
 */
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

/**
 * @brief 
 * Duplicates the standard output file descriptor in the child process.
 *
 * @details
 * If the file descriptor is greater than -1, it duplicates the 
 * file descriptor to the standard output.
 * If the file descriptor is less than 0, it duplicates the 
 * write end of the pipe to the standard output.
 *
 * @param fd The file descriptor.
 * @param pipes The pipe file descriptors.
 */
static void	child_write(int fd, int *pipes)
{
	if (fd > -1)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup");
			exit(EXIT_FAILURE);
		}
	}
	else if (fd < 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
		{
			perror("dup");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * @brief 
 * Processes the child processes.
 *
 * @details
 * Forks a new process. If the fork fails, it prints an error 
 * message and exits the program.
 * In the child process, it duplicates the standard output or input 
 * file descriptor depending on the mode, closes the pipe file descriptors, 
 * processes the minishell, frees the environment variables, and exits with 
 * the result of the minishell.
 *
 * @param data The shell data structure.
 * @param tree The command tree.
 * @param ch The child process ID.
 * @param mode The mode (0 for write, 1 for read).
 * @return The result of the minishell in the child process.
 */
static void	handle_child_process(t_minishell *data, t_tree *tree,
	pid_t *ch, int mode)
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
		exit((result >> 8) & 0xFF);
	}
	signal(SIGINT, SIG_IGN);
}

/**
 * @brief 
 * Processes the minishell.
 *
 * @details
 * If the tree has left and right children and the node is a pipe, it opens 
 * the pipe file descriptors, processes the child processes for write and read, 
 * closes the pipe file descriptors, waits for the child processes to finish, 
 * and returns the result of the last child process.
 * 
 * If the tree has left and right children and the node is not a pipe, 
 * it processes the minishell for the left child. If the node is a semicolon 
 * and the result is greater than EXIT_SUCCESS, or if the node is an and and 
 * the result is EXIT_SUCCESS, it processes the minishell for the right child.
 * 
 * If the tree does not have left and right children, 
 * it executes the command and returns the result.
 *
 * @param data The shell data structure.
 * @param tree The command tree.
 * @return The result of the minishell.
 */
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
			handle_child_process(data, tree, &child, 0);
			handle_child_process(data, tree, &child2, 1);
			close_pipes(data);
			waitpid(child, NULL, 0);
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

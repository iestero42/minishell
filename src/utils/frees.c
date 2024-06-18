/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:33:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/18 18:50:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file frees_bonus.c
 * @brief Contains functions for freeing memory and closing file descriptors.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Frees a command structure.
 *
 * @details
 * Frees the name and arguments of the command, and closes the input and output 
 * redirection file descriptors.
 *
 * @param cmd The command to free.
 */
void	free_cmd(void *cmd)
{
	t_command	*ptr;

	ptr = (t_command *) cmd;
	if (ptr)
	{
		if (ptr->args != NULL)
			double_free(ptr->args);
		if (ptr->name != NULL)
			free(ptr->name);
		if (ptr->output_redirect > -1)
			close(ptr->output_redirect);
		if (ptr->input_redirect > -1)
			close(ptr->input_redirect);
	}
	free(ptr);
}

/**
 * @brief 
 * Closes the pipe file descriptors.
 *
 * @details
 * Closes the read and write ends of the pipe. If an error occurs, 
 * it prints an error message.
 *
 * @param data The shell data structure.
 */
void	close_pipes(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (close(data->pipes[i]) < 0)
			perror("end");
		i++;
	}
}

/**
 * @brief 
 * Frees all allocated memory and restores the standard input and output.
 *
 * @details
 * Frees the command tree, and duplicates the standard input 
 * and output file descriptors to their original values.
 *
 * @param data The shell data structure.
 */
void	full_free(t_minishell *data)
{
	ft_clean_tree(&data->cmd_tree, free_cmd);
	dup2(data->std_fileno[0], 0);
	dup2(data->std_fileno[1], 1);
}

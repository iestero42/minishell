/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:33:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/19 10:00:00 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_command *cmd)
{
	if (cmd->args != NULL)
		double_free(cmd->args);
	if (cmd->name != NULL)
		free(cmd->name);
	if (cmd->output_redirect > -1)
		close(cmd->output_redirect);
	if (cmd->input_redirect > -1)
		close(cmd->input_redirect);
	if (access("here_doc", F_OK) != -1) 
		unlink("here_doc");
}

void	close_pipes(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < 2 * (data->n_comands - 1))
	{
		if (close(data->pipes[i]) < 0)
			perror("pipes");
		i++;
	}
}

void	full_free(t_minishell *data)
{
	int	i;


	i = 0;
	while (i < data->n_comands)
	{
		free_cmd(&data->comand_split[i]);
		i++;
	}
	free(data->comand_split);
	close_pipes(data);
	free(data->pipes);
	dup2(data->std_fileno[0], 0);
	dup2(data->std_fileno[1], 1);
}

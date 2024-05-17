/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:33:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:26:36 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	free_cmd(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->args != NULL)
			double_free(cmd->args);
		if (cmd->name != NULL)
			free(cmd->name);
		if (cmd->output_redirect > -1)
			close(cmd->output_redirect);
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
	}
}

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

void	full_free(t_minishell *data)
{
	ft_clean_tree(&data->cmd_tree, free_cmd);
	dup2(data->std_fileno[0], 0);
	dup2(data->std_fileno[1], 1);
}

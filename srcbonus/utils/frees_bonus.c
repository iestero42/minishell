/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:33:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:42:14 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

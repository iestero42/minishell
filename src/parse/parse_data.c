/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/16 09:48:16 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

static int	parse_list_command(char **command_list, t_minishell *data)
{
	int		i;

	i = -1;
	while (command_list[++i] != NULL)
	{
		if (parse_command(command_list[i], &data->comand_split[i], data, i)
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_list;

	g_signal = 0;
	command_list = split_pipes(command_line);
	if (!command_list)
		return (EXIT_FAILURE);
	data->n_comands = ft_dstrlen((const char **) command_list);
	data->comand_split = (t_command *) malloc(sizeof(t_command)
			* data->n_comands);
	if (!data->comand_split)
		error_init("malloc", 1);
	if (parse_list_command(command_list, data) == EXIT_FAILURE)
	{
		double_free(command_list);
		return (EXIT_FAILURE);
	}
	double_free(command_list);
	return (EXIT_SUCCESS);
}

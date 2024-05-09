/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/09 09:59:05 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

static int	parse_list_command(char **command_list, t_minishell *data)
{
	int			i;
	extern char	**environ;
	char		**tmp;

	i = -1;
	if (data->access_environ == 0)
	{
		tmp = ft_dstrdup(environ);
		free(environ);
		environ = tmp;
		data->access_environ = 1;
	}
	while (command_list[++i] != NULL)
	{
		if (parse_command(command_list[i], &data->comand_split[i], data, i)
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_data(char *command_line, t_minishell *data)
{
	char		**command_list;

	g_signal = 0;
	command_list = split_pipes(command_line);
	if (!command_list)
		return (EXIT_FAILURE);
	data->n_comands = ft_dstrlen(command_list);
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

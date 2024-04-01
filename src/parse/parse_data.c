/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 09:59:47 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_list_command(char **command_list, t_minishell *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (command_list[++i] != NULL)
	{
		tmp = ft_itoa(i);
		data->comand_split[i].here_doc = ft_strjoin(ft_strdup("/tmp/heredoc"),
				tmp);
		if (!data->comand_split[i].here_doc)
			error_init("ft_strjoin");
		free(tmp);
		parse_command(command_list[i], &data->comand_split[i], data->cmd_list,
			data->last_status_cmd);
	}
}

void	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_list;

	command_list = split_pipes(command_line);
	if (!command_list)
		error_init("split_pipes");
	data->n_comands = ft_dstrlen((const char **) command_list);
	data->comand_split = (t_command *) malloc(sizeof(t_command)
			* data->n_comands);
	if (!data->comand_split)
		error_init("malloc");
	parse_list_command(command_list, data);
	double_free(command_list);
}

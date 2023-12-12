/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/12 11:46:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_command(char **command)
{
	int	i;
	int	size;

	while (command[i] != '\0')
	{
		if (!ft_strcmp(command[i], "|"))
			size++;
	}
	return (size);
}

static void	parse_list_command(char **command_list, t_minishell *data)
{
	int			current;
	int			prev;

	current = -1;
	prev = 0;
	while (command_list[++current] != '\0')
	{
		if (!ft_strcmp(command_list[current], "|"))
		{
			*++data->comand_split = parse_command(ft_substr_array(command_list,
						prev, current));
			prev = current + 1;
		}
	}
	*++data->comand_split = parse_command(ft_substr_array(command_list,
				prev, current));
}

void	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_split;


	command_split = ft_split(command_line, ' ');
	if (!command_split)
		error_malloc();
	while (!ft_strcmp(command_split[ft_dstrlen(command_split) - 1], "|"))
	{
		double_free(command_split);
		command_split = ft_split(readline("pipe> "), ' ');
		if (!command_split)
			error_malloc();
	}
	data->comand_split = (t_command *) malloc(sizeof(t_command)
			* calc_command(command_split));
	if (!data->comand_split)
		error_malloc();
	parse_list_command(command_split, data);
}

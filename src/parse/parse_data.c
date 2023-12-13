/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/13 12:04:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_command(char **command)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (command[i] != '\0')
	{
		if (!ft_strcmp(command[i], "|"))
			size++;
		i++;
	}
	return (size);
}

static void	parse_list_command(char **command_list, t_minishell *data)
{
	int			current;
	int			prev;
	int			i;

	current = -1;
	prev = 0;
	i = 0;
	while (command_list[++current] != NULL)
	{
		if (!ft_strcmp(command_list[current], "|"))
		{
			data->comand_split[i++] = parse_command(ft_dsubstr(command_list,
						prev, current));
			prev = current + 1;
		}
	}
	data->comand_split[i] = parse_command(ft_dsubstr(command_list,
				prev, current));
}

void	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_split;
	char		**tmp;


	command_split = split_command(command_line);
	if (!command_split)
		error_malloc();
	while (!ft_strcmp(command_split[
				ft_dstrlen((const char **) command_split) - 1], "|"))
	{
		tmp = split_command(readline("pipe> "));
		if (!tmp)
			error_malloc();
		command_split = ft_dstrjoin(command_split, tmp);
	}
	data->comand_split = (t_command *) malloc(sizeof(t_command)
			* calc_command(command_split));
	if (!data->comand_split)
		error_malloc();
	parse_list_command(command_split, data);
}

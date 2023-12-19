/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/19 10:02:10 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_command(char **command)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (command[i] != NULL)
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
			parse_command(ft_dsubstr(command_list, prev, current),
				&data->comand_split[i++]);
			prev = current + 1;
		}
	}
	parse_command(ft_dsubstr(command_list, prev, current),
		&data->comand_split[i]);
}

void	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_split;
	char		**tmp;

	if (split_command(command_line, &command_split) == EXIT_FAILURE)
		error_malloc();
	while (!ft_strcmp(command_split[
				ft_dstrlen((const char **) command_split) - 1], "|"))
	{
		if (split_command(readline("pipe> "), &tmp) == EXIT_FAILURE)
			error_malloc();
		command_split = ft_dstrjoin(command_split, tmp);
	}
	data->comand_split = (t_command *) malloc(sizeof(t_command)
			* calc_command(command_split));
	if (!data->comand_split)
		error_malloc();
	ft_putstr_fd("hola", 1);
	parse_list_command(command_split, data);
}

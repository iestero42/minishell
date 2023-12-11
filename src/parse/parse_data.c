/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/11 11:54:45 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dstrlen(const char **str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	parse_data(const char *command_line, t_minishell *data)
{
	char		**command_split;
	t_command	command;
	int			len;

	command_split = ft_split(command_line, '|');
	if (!command_split)
		return (EXIT_FAILURE);
	len = -1;
	while (command_split[++len] != '\0')
	{
		command = parse_command(command_split[len]);
		data->comand_split[len] = command;
	}
	return (EXIT_SUCCESS);
}

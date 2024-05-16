/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/16 08:38:44 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

static int	parse_list_command(char *command_line, t_minishell *data)
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
	if (parse_command_new(command_line, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_data(char *command_line, t_minishell *data)
{
	char		**command_list;
	
	g_signal = 0;
	if (parse_list_command(command_line, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

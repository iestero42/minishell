/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 08:45:57 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_n_flag(char **args, int *pos)
{
	int	i;
	int	j;

	j = -1;
	while (args[1][++j] != '\0')
		if (args[1][j] != 'n')
			return (EXIT_FAILURE);
	i = 0;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '-')
		{
			j = -1;
			while (args[i][++j] != '\0')
				if (args[i][j] != 'n')
					break ;
			if (args[i][j] == '\0')
				*pos = *pos + 1;
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

int	built_echo(char **args)
{
	int	add_newline;
	int	len;
	int	i;

	add_newline = 1;
	i = 1;
	len = ft_dstrlen(args);
	if (len > 1 && check_n_flag(args, &i))
		add_newline = 0;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i < len - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (add_newline)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

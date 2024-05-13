/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 09:14:31 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_flag(char **args, int *pos)
{
	int	i;
	int	j;

	j = 1;
	while (args[1][0] == '-' && args[1][j] != '\0' && args[1][j] == 'n')
		j++;
	if (args[1][j] != '\0')
		return (EXIT_FAILURE);
	i = 0;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j] != '\0' && args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				*pos = *pos + 1;
			else
				break ;
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
	if (len > 1 && !check_n_flag(args, &i))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:59:11 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 09:26:04 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (EXIT_FAILURE);
			}
			j++;
		}
	}
	return (EXIT_SUCCESS);
}

int	built_exit(char **args)
{
	int			i;
	extern char	**environ;

	i = ft_dstrlen(args);
	ft_putstr_fd("exit\n", 1);
	if (check_args(args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (i > 2)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		if (i > 1)
			i = ft_atoi(args[1]);
		else
			i = 0;
		double_free(environ);
		exit(i);
	}
	return (EXIT_SUCCESS);
}

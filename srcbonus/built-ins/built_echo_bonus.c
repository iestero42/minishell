/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_echo(char **args)
{
	int	add_newline;
	int	len;
	int	i;

	add_newline = 1;
	i = 1;
	len = ft_dstrlen(args);
	if (len > 1 && !ft_strcmp(args[1], "-n"))
	{
		add_newline = 0;
		i++;
	}
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

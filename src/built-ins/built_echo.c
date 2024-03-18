/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:27:09 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd(args[i], 1);
		if (i < len - 1)
			ft_putstr_fd(" ", 1);
	}
	if (add_newline)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

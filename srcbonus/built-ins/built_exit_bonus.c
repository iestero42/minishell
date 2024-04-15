/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:59:11 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:40:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_exit(char **args)
{
	int	i;

	i = ft_dstrlen((const char **) args);
	if (i > 2)
		ft_putstr_fd("exit: too many arguments", 2);
	else
	{
		if (i > 1)
			i = ft_atoi(args[1]);
		else
			i = 0;
		exit(i);
	}
	return (EXIT_SUCCESS);
}

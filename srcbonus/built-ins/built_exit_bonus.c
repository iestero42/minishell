/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:59:11 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/07 12:20:42 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_exit(char **args)
{
	int			i;
	extern char	**environ;

	i = ft_dstrlen(args);
	if (i > 2)
		ft_putstr_fd("exit: too many arguments", 2);
	else
	{
		if (i > 1)
			i = ft_atoi(args[1]);
		else
			i = 0;
		printf("exit\n");
		double_free(environ);
		exit(i);
	}
	return (EXIT_SUCCESS);
}

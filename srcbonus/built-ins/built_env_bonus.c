/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:52 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "LINES", 5)
			&& ft_strncmp(environ[i], "COLUMNS", 7))
		{
			ft_putstr_fd(environ[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

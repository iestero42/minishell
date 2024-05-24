/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:52 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:42:12 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_env_bonus.c
 * @brief Contains the built_env function for printing environment variables.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Prints the environment variables to the standard output.
 *
 * @details
 * Iterates over the environment variables. For each variable, 
 * if the variable is not "LINES" or "COLUMNS", it prints the variable 
 * and a newline.
 *
 * @return EXIT_SUCCESS.
 */
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

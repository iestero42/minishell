/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:27 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/17 08:31:34 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_unset_bonus.c
 * @brief Contains the built_unset function for unsetting environment variables.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Unsets an environment variable.
 *
 * @details
 * If the environment variable starts with the same string as the argument 
 * and the next character is '=', it frees the environment variable and shifts 
 * the rest of the environment variables to the left.
 *
 * @param env The environment variable to unset.
 * @param arg The argument.
 */
static void	unset_aux(char **env, char *arg)
{
	char	**p;

	if (!ft_strncmp(*env, arg, ft_strlen(arg))
		&& (*env)[ft_strlen(arg)] == '=')
	{
		p = env;
		free(*env);
		while (*p != NULL)
		{
			*p = *(p + 1);
			p++;
		}
	}
}

/**
 * @brief 
 * Unsets environment variables.
 *
 * @details
 * Iterates over the arguments. For each argument, it iterates over 
 * the environment variables and unsets the environment variable.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS.
 */
int	built_unset(char **args)
{
	int			i;
	char		**env_tmp;
	extern char	**environ;

	i = 0;
	while (args[++i] != NULL)
	{
		env_tmp = environ;
		while (*env_tmp != NULL)
		{
			unset_aux(env_tmp, args[i]);
			env_tmp++;
		}
	}
	return (EXIT_SUCCESS);
}

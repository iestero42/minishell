/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:27 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:27 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/22 11:51:06 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_unset(char **args)
{
	extern char	**environ;
	int			i;
	char		**p;
	char		**env;

	i = 0;
	while (args[++i] != NULL)
	{
		env = environ;
		while (*env != NULL)
		{
			if (!ft_strncmp(*env, args[i], ft_strlen(args[i]))
				&& (*env)[ft_strlen(args[i])] == '=')
			{
				p = env;
				while (*p != NULL)
				{
					*p = *(p + 1);
					p++;
				}
			}
			env++;
		}
	}
	return (EXIT_SUCCESS);
}

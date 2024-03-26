/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:27 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/26 13:30:10 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_unset(char **args, char ***env)
{
	int			i;
	char		**p;
	char		**env_tmp;

	i = 0;
	while (args[++i] != NULL)
	{
		env_tmp = *env;
		while (*env != NULL)
		{
			if (!ft_strncmp(*env_tmp, args[i], ft_strlen(args[i]))
				&& (*env_tmp)[ft_strlen(args[i])] == '=')
			{
				p = env_tmp;
				while (*p != NULL)
				{
					*p = *(p + 1);
					p++;
				}
			}
			env_tmp++;
		}
	}
	return (EXIT_SUCCESS);
}

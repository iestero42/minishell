/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_cd(char **args)
{
	int		len;
	char	*dir;

	len = ft_dstrlen(args);
	dir = NULL;
	if (len == 1)
	{
		dir = getenv("HOME");
		if (chdir(dir) != 0)
			perror(dir);
	}
	else if (!ft_strcmp(args[1], "~"))
	{
		dir = getenv("HOME");
		if (chdir(dir) != 0)
			perror(dir);
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror(args[1]);
	}
	return (EXIT_SUCCESS);
}

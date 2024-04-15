/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:40:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	built_cd(char **args)
{
	int		len;
	char	*dir;

	len = ft_dstrlen((const char **) args);
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

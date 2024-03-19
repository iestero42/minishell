/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/19 10:08:36 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_cd(char **args)
{
	int		len;
	char	*dir;

	len = ft_dstrlen((const char **) args);
	dir = NULL;
	if (len > 1)
	{
		if (chdir(args[1]) != 0)
			perror(args[1]);
	}
	else if (len == 1)
	{
		dir = getenv("HOME");
		if (dir == NULL)
			perror("HOME");
	}
	return (EXIT_SUCCESS);
}

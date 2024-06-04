/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/04 09:27:11 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_cd_bonus.c
 * @brief Contains the built_cd function for changing the current directory.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Changes the current directory.
 *
 * @details
 * If no arguments are provided, it changes the directory to the home directory.
 * If the argument is "~", it changes the directory to the home directory.
 * Otherwise, it changes the directory to the specified directory.
 * If an error occurs, it prints an error message.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS.
 */
int	built_cd(char **args)
{
	int		len;
	char	*dir;

	len = ft_dstrlen(args);
	dir = NULL;
	if (len == 1 || !ft_strcmp(args[1], "~"))
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

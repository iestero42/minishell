/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:58 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:47:11 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_pwd_bonus.c
 * @brief Contains the built_pwd function for printing the current directory.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Prints the current directory to the standard output.
 *
 * @details
 * Gets the current directory and stores it in a buffer.
 * If the current directory is not NULL, it prints the current 
 * directory and a newline.
 * If the current directory is NULL, it prints an error message.
 *
 * @return EXIT_SUCCESS.
 */
int	built_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		perror("pwd");
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/17 08:31:34 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_echo_bonus.c
 * @brief Contains the built_echo function for printing to the standard output.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Checks for the '-n' flag in the arguments.
 *
 * @details
 * Iterates over the arguments. If an argument starts with '-', 
 * it checks if the rest of the argument is 'n'.
 * If the argument is '-n', it increments the position.
 * If the argument is not '-n', it breaks the loop.
 *
 * @param args The array of arguments.
 * @param pos The position to set.
 * @return EXIT_SUCCESS if the '-n' flag is found, otherwise EXIT_FAILURE.
 */
static int	check_n_flag(char **args, int *pos)
{
	int	i;
	int	j;

	j = 1;
	while (args[1][0] == '-' && args[1][j] != '\0' && args[1][j] == 'n')
		j++;
	if (args[1][j] != '\0' || j == 1)
		return (EXIT_FAILURE);
	i = 0;
	while (args[++i] != NULL)
	{
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j] != '\0' && args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				*pos = *pos + 1;
			else
				break ;
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Prints the arguments to the standard output.
 *
 * @details
 * If the '-n' flag is not found in the arguments, it sets add_newline to 1.
 * Iterates over the arguments starting from the position 
 * set by check_n_flag. For each argument, it prints the argument and a 
 * space if it is not the last argument. If add_newline is 1, it prints 
 * a newline.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS.
 */
int	built_echo(char **args)
{
	int	add_newline;
	int	len;
	int	i;

	add_newline = 1;
	i = 1;
	len = ft_dstrlen(args);
	if (len > 1 && !check_n_flag(args, &i))
		add_newline = 0;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i < len - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (add_newline)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

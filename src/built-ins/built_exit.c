/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:59:11 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/17 08:31:34 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_exit_bonus.c
 * @brief Contains the built_exit function for exiting the shell.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Checks the arguments for numeric values.
 *
 * @details
 * Iterates over the arguments. For each argument, it checks if 
 * all characters are digits. If a character is not a digit, it prints an 
 * error message and returns EXIT_FAILURE.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS if all characters are digits, otherwise EXIT_FAILURE.
 */
static int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (EXIT_FAILURE);
			}
			j++;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Exits the shell.
 *
 * @details
 * Prints "exit" to the standard output.
 * Checks the arguments for numeric values. If the check fails, 
 * it returns EXIT_FAILURE.
 * If there are more than 2 arguments, it prints an error message.
 * If there is more than 1 argument, it converts the second argument
 * to an integer.
 * If there is only 1 argument, it sets the exit status to 0.
 * Frees the environment variables and exits with the exit status.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS.
 */
int	built_exit(char **args)
{
	int			i;
	extern char	**environ;

	i = ft_dstrlen(args);
	ft_putstr_fd("exit\n", 1);
	if (check_args(args) == EXIT_FAILURE)
		return (EXIT_FAILURE << 8);
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (EXIT_FAILURE << 8);
	}
	else
	{
		if (i > 1)
			i = ft_atoi(args[1]);
		else
			i = 0;
		double_free(environ);
		exit(i);
	}
	return (EXIT_SUCCESS);
}

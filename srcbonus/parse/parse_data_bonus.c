/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 15:25:19 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

/**
 * @file parse_data_bonus.c
 * @brief Contains the function for parsing data.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

/**
 * @brief 
 * Parses the command line data.
 *
 * @details
 * This function trims the command line, checks if it's empty, and if not,
 * parses the command and returns the result.
 *
 * @param command_line The command line to parse.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure or 
 * 	if the command line is empty.
 */
int	parse_data(char *command_line, t_minishell *data)
{
	char	*tmp;
	int		result;

	g_signal = 0;
	tmp = ft_strtrim(command_line, " ");
	if (!tmp)
		error_init("ft_strtrim", 1);
	if (*tmp == '\0')
	{
		free(tmp);
		return (EXIT_FAILURE);
	}
	result = parse_command(tmp, data);
	free(tmp);
	return (result);
}

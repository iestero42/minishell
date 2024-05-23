/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:31:40 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 15:17:59 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/**
 * @file parse_args_bonus.c
 * @brief Contains the function for parsing arguments.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

/**
 * @brief 
 * Parses the arguments from the tokens and stores them in the command structure.
 *
 * @details
 * This function iterates over the tokens. If a token is not empty, 
 * it appends it to the arguments array. Finally, it assigns the arguments 
 * array to the args field of the command structure.
 *
 * @param cmd The command structure where the arguments will be stored.
 * @param tokens The tokens to be parsed into arguments.
 * @return Always returns EXIT_SUCCESS.
 */
int	parse_args(t_command *cmd, char **tokens)
{
	int		i;
	char	**args;

	i = 0;
	args = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] != '\0')
			args = ft_append(args, tokens[i]);
		i++;
	}
	cmd->args = args;
	return (EXIT_SUCCESS);
}

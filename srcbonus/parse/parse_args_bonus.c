/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:31:40 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

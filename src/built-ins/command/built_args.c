/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:31:40 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 11:29:09 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_args(t_command *cmd, char **tokens)
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

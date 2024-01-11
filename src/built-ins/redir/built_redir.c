/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:21:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/08 08:37:39 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	built_redirect(char **tokens, t_command *cmd)
{
	int	i;

	i = 0;
	cmd->output_redirect = -2;
	cmd->input_redirect = -2;
	while (tokens[i] != NULL)
	{
		if (built_output(tokens[i], cmd, tokens[i + 1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (built_input(tokens[i], cmd, tokens[i + 1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

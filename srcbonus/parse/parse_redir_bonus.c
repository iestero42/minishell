/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:21:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h" 

int	parse_redirect(char **tokens, t_command *cmd, int pos, t_minishell *data)
{
	int	i;

	i = -1;
	cmd->output_redirect = -2;
	cmd->input_redirect = -2;
	while (tokens[++i] != NULL && data->status != STOPPED)
	{
		if (parse_output(&tokens[i], cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (parse_input(&tokens[i], cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

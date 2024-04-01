/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:48:07 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 12:28:33 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_command(t_command *cmd)
{
	cmd->type = ERROR_COMMAND;
}

void	parse_command(char *command_str, t_command *cmd, t_minishell *data,
			int pos)
{
	char	**tokens;
	char	*cmd_trimmed;

	cmd_trimmed = ft_strtrim(command_str, " ");
	if (!cmd_trimmed)
		return (error_init("ft_strtrim"));
	tokens = split_command(cmd_trimmed);
	if (tokens == NULL)
		return (error_command(cmd));
	free(cmd_trimmed);
	if (parse_redirect(tokens, cmd, data, pos) == EXIT_FAILURE)
		return (error_command(cmd));
	if (parse_command_name(tokens, cmd, data->cmd_list,
			data->last_status_cmd) == EXIT_FAILURE)
		return (error_command(cmd));
	if (built_args(cmd, tokens) == EXIT_FAILURE)
		return (error_command(cmd));
	double_free(tokens);
	return (EXIT_SUCCESS);
}

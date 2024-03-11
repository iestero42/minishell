/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:48:07 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/11 09:18:30 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_command(char *msg)
{
	printf("%s", msg);
	return (EXIT_FAILURE);
}

int	parse_command(char *command_str, t_command *cmd, char **cmd_list)
{
	char	**tokens;
	char	*cmd_trimmed;

	cmd_trimmed = ft_strtrim(command_str, " ");
	if (!cmd_trimmed)
		return (error_command("fuc"));
	tokens = split_command(cmd_trimmed);
	free(cmd_trimmed);
	if (tokens == NULL)
		return (error_command("fuc"));
	if (built_env_variable(tokens, cmd->last_status) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (built_redirect(tokens, cmd) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (trim_command(tokens) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (built_command(tokens, cmd, cmd_list) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (built_args(cmd, tokens) == EXIT_FAILURE)
		return (error_command("fuc"));
	double_free(tokens);
	return (EXIT_SUCCESS);
}

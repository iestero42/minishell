/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:48:07 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/11 13:19:33 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_command(char *msg)
{
	printf("%s", msg);
	return (EXIT_FAILURE);
}

int	parse_command(char *command_str, t_command *cmd)
{
	char	**tokens;

	tokens = split_command(command_str);
	if (tokens == NULL)
		return (error_command("fuc"));
	if (built_env_variable(tokens) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (built_redirect(tokens, cmd) == EXIT_FAILURE)
		return (error_command("fuc"));
	if (built_command(tokens, cmd) == EXIT_FAILURE)
		return (error_command("fuc"));
	free(tokens);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_name_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:18:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/03 10:55:10 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_command_name_bonus.c
 * @brief Contains the functions for parsing command names.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Prints an error message and returns EXIT_FAILURE.
 *
 * @param cmd The command that was not found.
 * @return Always returns EXIT_FAILURE.
 */
static int	print_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (EXIT_FAILURE);
}

/**
 * @brief 
 * Checks if the token is a path command.
 *
 * @details
 * If the command name is not set, it iterates over the directories,
 * constructs the absolute path, and checks if it is executable.
 * If it is, it sets the command name and type.
 *
 * @param token The token to check.
 * @param dirs The directories to check.
 * @param cmd The command structure to modify.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	check_path(char *token, char **dirs, t_command *cmd)
{
	char	abs_path[1024];
	int		i;

	if (!cmd->name)
	{
		i = -1;
		while (dirs[++i] != NULL)
		{
			ft_memset(abs_path, 0, sizeof(abs_path));
			ft_strlcat(abs_path, dirs[i], sizeof(abs_path));
			ft_strlcat(abs_path, "/", sizeof(abs_path));
			ft_strlcat(abs_path, token, sizeof(abs_path));
			if (!access(abs_path, X_OK))
			{
				cmd->name = ft_strdup(abs_path);
				if (!cmd->name)
					error_init("malloc", 1);
				cmd->type = PATH_COMMAND;
				break ;
			}
		}
		if (cmd->name == NULL)
			return (print_error(token));
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Checks if the token is a relative path command.
 *
 * @details
 * If the command name is not set, it checks if the token is executable.
 * If it is, it sets the command name and type.
 *
 * @param token The token to check.
 * @param cmd The command structure to modify.
 * @return Always returns EXIT_SUCCESS.
 */
static int	check_relative_path(char *token, t_command *cmd)
{
	if (!cmd->name)
	{
		if (!access(token, X_OK))
		{
			cmd->name = ft_strdup(token);
			if (!cmd->name)
				error_init("malloc", 1);
			cmd->type = PATH_COMMAND;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Checks if the token is an own command.
 *
 * @details
 * Iterates over the command list and compares each command with the token.
 * If they match, it sets the command name and type.
 *
 * @param token The token to check.
 * @param cmd The command structure to modify.
 * @param cmd_list The list of own commands.
 * @return Always returns EXIT_SUCCESS.
 */
static int	check_own_command(char *token, t_command *cmd, char **cmd_list)
{
	int		i;

	i = -1;
	while (++i < NUM_COMMANDS)
	{
		if (!ft_strcmp(token, cmd_list[i]))
		{
			cmd->name = ft_strdup(token);
			if (!cmd->name)
				error_init("malloc", 1);
			cmd->type = i + 1;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Parses the command name from the tokens.
 *
 * @details
 * Converts the tokens, gets the PATH environment variable, 
 * splits it into directories, and checks if the first non-empty 
 * token is an own command, a relative path command,
 * or a path command.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to fill.
 * @param cmd_list The list of own commands.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	parse_command_name(char **tokens, t_command *cmd, char **cmd_list)
{
	int		i;
	char	*path;
	char	**dirs;

	convert_tokens(tokens);
	cmd->name = NULL;
	cmd->type = -1;
	i = 0;
	while (tokens[i] != NULL && tokens[i][0] == '\0')
		i++;
	if (tokens[i] == NULL || tokens[i][0] == '\0')
		return (EXIT_FAILURE);
	path = getenv("PATH");
	dirs = ft_split(path, ':');
	if (!dirs)
		error_init("malloc", 1);
	check_own_command(tokens[i], cmd, cmd_list);
	check_relative_path(tokens[i], cmd);
	if (check_path(tokens[i], dirs, cmd) == EXIT_FAILURE)
	{
		double_free(dirs);
		return (EXIT_FAILURE);
	}
	double_free(dirs);
	return (EXIT_SUCCESS);
}

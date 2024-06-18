/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_name_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:18:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/18 15:48:38 by yunlovex         ###   ########.fr       */
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
	char		abs_path[1024];
	int			i;
	struct stat	path_stat;

	if (!cmd->name && !ft_strchr(token, '/'))
	{
		i = -1;
		while (dirs != NULL && dirs[++i] != NULL)
		{
			ft_memset(abs_path, 0, sizeof(abs_path));
			ft_strlcat(abs_path, dirs[i], sizeof(abs_path));
			ft_strlcat(abs_path, "/", sizeof(abs_path));
			ft_strlcat(abs_path, token, sizeof(abs_path));
			stat(abs_path, &path_stat);
			if (!access(abs_path, X_OK) && !S_ISDIR(path_stat.st_mode))
			{
				cmd->name = ft_strdup(abs_path);
				if (!cmd->name)
					error_init("malloc", 1);
				cmd->type = PATH_COMMAND;
				break ;
			}
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
	int	len;

	if (!cmd->name)
	{
		len = ft_strlen(token);
		if ((len > 1 && token[0] == '.' && token[1] == '/')
			|| (len > 0 && token[0] == '/')
			|| (len > 2 && token[0] == '.'
				&& token[1] == '.' && token[2] == '/'))
		{
			if (!access(token, X_OK))
			{
				cmd->name = ft_strdup(token);
				if (!cmd->name)
					error_init("malloc", 1);
				cmd->type = PATH_COMMAND;
			}
		}
		else
		{
			cmd->name = ft_strdup(token);
			return (EXIT_FAILURE);
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
	int		error;

	cmd->name = NULL;
	cmd->type = -1;
	i = 0;
	convert_tokens(tokens);
	path = getenv("PATH");
	while (tokens[i] != NULL && tokens[i][0] == '\5')
		i++;
	if (tokens[i] == NULL || tokens[i][0] == '\5')
		return (EXIT_SUCCESS);
	dirs = ft_split(path, ':');
	if (!dirs && path)
		error_init("malloc", 1);
	check_own_command(tokens[i], cmd, cmd_list);
	check_path(tokens[i], dirs, cmd);
	error = check_relative_path(tokens[i], cmd);
	if (dirs)
		double_free(dirs);
	return (error);
}

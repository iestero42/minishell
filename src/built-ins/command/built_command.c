/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:18:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/11 10:52:28 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *token, char **dirs, t_command *cmd)
{
	char	*path;
	char	abs_path[1024];
	int		i;

	path = ft_strtrim(token, "\"");
	if (!path)
		return (EXIT_FAILURE);
	i = 0;
	while (dirs[i] != NULL)
	{
		ft_memset(abs_path, 0, sizeof(abs_path));
		ft_strlcat(abs_path, dirs[i], sizeof(abs_path));
		ft_strlcat(abs_path, "/", sizeof(abs_path));
		ft_strlcat(abs_path, path, sizeof(abs_path));
		if (!access(abs_path, X_OK))
		{
			cmd->name = abs_path;
			cmd->type = PATH_COMMAND;
		}
	}
	free(path);
	if (cmd->name == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_relative_path(char *token, t_command *cmd)
{
	char	*rel_path;

	rel_path = ft_strtrim(token, "\"");
	if (!rel_path)
		return (EXIT_FAILURE);
	if (!access(rel_path, X_OK))
	{
		cmd->name = rel_path;
		cmd->type = PATH_COMMAND;
	}
	return (EXIT_SUCCESS);
}

static int	check_own_command(char *token, t_command *cmd)
{
	char	*name;
	char	*list_commands[NUM_COMMANDS];
	int		i;

	name = ft_strtrim(token, "\"");
	if (!name)
		return (EXIT_FAILURE);
	list_commands[0] = "echo";
	list_commands[1] = "cd";
	list_commands[2] = "pwd";
	list_commands[3] = "export";
	list_commands[4] = "unset";
	list_commands[5] = "env";
	list_commands[6] = "exit";
	i = 0;
	while (i < NUM_COMMANDS)
	{
		if (!ft_strcmp(name, list_commands[i]))
		{
			cmd->name = name;
			cmd->type = OWN_COMMAND;
		}
	}
	return (EXIT_SUCCESS);
}

int	built_command(char **tokens, t_command *cmd)
{
	int		i;
	char	*path;
	char	**dirs;

	cmd->name = NULL;
	cmd->type = -1;
	path = getenv("PATH");
	dirs = ft_split(path, ':');
	if (!dirs)
		return (EXIT_FAILURE);
	i = 0;
	while (!ft_strcmp(tokens[i], ""))
		i++;
	if (check_own_command(tokens[i], cmd) == EXIT_FAILURE
		|| check_relative_path(tokens[i], cmd) == EXIT_FAILURE
		|| check_path(tokens[i], dirs, cmd) == EXIT_FAILURE)
	{
		double_free(dirs);
		return (EXIT_FAILURE);
	}
	double_free(dirs);
	return (EXIT_SUCCESS);
}

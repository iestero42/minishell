/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:18:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/04 09:22:33 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *token, char **dirs, t_command *cmd)
{
	char	abs_path[1024];
	int		i;

	if (!cmd->name)
	{
		i = 0;
		while (dirs[i] != NULL)
		{
			ft_memset(abs_path, 0, sizeof(abs_path));
			ft_strlcat(abs_path, dirs[i], sizeof(abs_path));
			ft_strlcat(abs_path, "/", sizeof(abs_path));
			ft_strlcat(abs_path, token, sizeof(abs_path));
			if (!access(abs_path, X_OK))
			{
				cmd->name = ft_strdup(abs_path);
				cmd->type = PATH_COMMAND;
			}
		}
		if (cmd->name == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_relative_path(char *token, t_command *cmd)
{
	if (!cmd->name)
	{
		if (!access(token, X_OK))
		{
			cmd->name = ft_strdup(token);
			cmd->type = PATH_COMMAND;
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_own_command(char *token, t_command *cmd, char **cmd_list)
{
	int		i;

	i = -1;
	while (++i < NUM_COMMANDS)
	{
		if (!ft_strcmp(token, cmd_list[i]))
		{
			cmd->name = ft_strdup(token);
			cmd->type = OWN_COMMAND;
		}
	}
	return (EXIT_SUCCESS);
}

int	built_command(char **tokens, t_command *cmd, char **cmd_list)
{
	int		i;
	char	*path;
	char	**dirs;

	cmd->name = NULL;
	cmd->type = -1;
	path = getenv("PATH");
	dirs = ft_split(path, ':');
	i = 0;
	while (tokens[i][0] == '\0')
		i++;
	if (check_own_command(tokens[i], cmd, cmd_list) == EXIT_FAILURE
		|| check_relative_path(tokens[i], cmd) == EXIT_FAILURE
		|| check_path(tokens[i], dirs, cmd) == EXIT_FAILURE)
	{
		double_free(dirs);
		return (EXIT_FAILURE);
	}
	if (dirs)
		double_free(dirs);
	return (EXIT_SUCCESS);
}

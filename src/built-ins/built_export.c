/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/22 12:09:13 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_environ_aux(char *arg, char **env)
{

	env = ft_realloc(env,
			(ft_dstrlen((const char **) env) + 2) * sizeof(char *));
	if (env == NULL)
		return (EXIT_FAILURE);
	env[ft_dstrlen((const char **) env)] = ft_strdup(arg);
	env[ft_dstrlen((const char **) env) + 1] = NULL;
	return (EXIT_SUCCESS);
}

static int	replace_environ(char *arg, char **env)
{
	char		**env_tmp;
	char		**var;	

	env_tmp = env;
	var = ft_split(arg, '=');
	if (!var)
		return (EXIT_FAILURE);
	while (*env != NULL)
	{
		if (!ft_strncmp(*env_tmp, var[0], ft_strlen(var[0]))
			&& (*env_tmp)[strlen(var[0])] == '=')
		{
			*env_tmp = ft_strdup(arg);
			break ;
		}
		env_tmp++;
	}
	if (*env_tmp == NULL)
		if (replace_environ_aux(arg, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_export(char **args, char **env)
{
	int			i;

	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0] == '\'' | args[i][0] == '\"' | args[i][0] == '=')
		{
			ft_putstr_fd("export:", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (EXIT_FAILURE);
		}
		else
			replace_environ(args[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}

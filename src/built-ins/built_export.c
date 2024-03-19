/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/19 10:11:19 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_environ_aux(char *arg)
{
	extern char	**environ;

	environ = ft_realloc(environ,
			(ft_dstrlen((const char **) environ) + 2) * sizeof(char *));
	if (environ == NULL)
		return (EXIT_FAILURE);
	environ[ft_dstrlen((const char **) environ)] = arg;
	environ[ft_dstrlen((const char **) environ) + 1] = NULL;
	return (EXIT_SUCCESS);
}

static int	replace_environ(char *arg)
{
	extern char	**environ;
	char		**env;
	char		**var;	

	env = environ;
	var = ft_split(arg, '=');
	if (!var)
		return (EXIT_FAILURE);
	while (*env != NULL)
	{
		if (!ft_strncmp(*env, var[0], ft_strlen(var[0]))
			&& (*env)[strlen(var[0])] == '=')
		{
			*env = arg;
			break ;
		}
	}
	if (*env == NULL)
		if (replace_environ_aux(arg) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_export(char **args)
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
			replace_environ(args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

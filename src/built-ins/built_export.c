/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:27:15 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_environ_aux(char *arg)
{
	extern char	**environ;
	char		**env;

	environ = ft_realloc(environ,
			(ft_dstrlen(environ) + 2) * sizeof(char *));
	if (environ == NULL)
		return (EXIT_FAILURE);
	environ[ft_dstrlen(environ)] = arg;
	environ[ft_dstrlen(environ) + 1] = NULL;
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
	char		**var;
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
		}
		else
			replace_environ(args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

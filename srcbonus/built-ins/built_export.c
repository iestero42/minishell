/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 08:54:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_export(char *arg, int len)
{
	char	**var;
	char	*substr;
	int		i;

	i = -1;
	var = (char **) malloc(sizeof(char *) * 3);
	while (++i < len)
	{
		if (arg[i] == '=')
			break ;
	}
	substr = ft_substr(arg, 0, i);
	if (!substr)
		error_init("malloc", 1);
	var[0] = substr;
	var[1] = ft_strdup(&arg[i + 1]);
	var[2] = NULL;
	return (var);
}

static int	error_export(char **var, char *arg)
{
	int	i;

	if (!var)
		error_init("malloc", 1);
	if (arg[0] == '=' || ft_isdigit(arg[0])
		|| error_unclosed_quotes(var[1], ft_strlen(var[1])))
	{
		error_export_msg(arg);
		return (EXIT_FAILURE);
	}
	if (var[0][0] == '_')
		return (-2);
	i = -1;
	while (var[0][++i] != '\0')
		if (ft_isalnum(var[0][i]) == 0)
			break ;
	if (var[0][i] != '\0')
	{
		error_export_msg(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	replace_environ_aux(char *arg)
{
	extern char	**environ;

	environ = ft_realloc(environ, arg,
			ft_dstrlen(environ), 2);
	if (environ == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	replace_environ(char **var, char *arg)
{
	char		**env_tmp;
	extern char	**environ;

	env_tmp = environ;
	while (*env_tmp != NULL)
	{
		if (!ft_strncmp(*env_tmp, var[0], ft_strlen(var[0]))
			&& (*env_tmp)[strlen(var[0])] == '=')
		{
			free(*env_tmp);
			*env_tmp = ft_strdup(arg);
			break ;
		}
		env_tmp++;
	}
	if (*env_tmp == NULL)
		if (replace_environ_aux(arg) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_export(char **args)
{
	int			i;
	int			error;
	char		**var;

	i = 0;
	var = 0;
	error = EXIT_SUCCESS;
	while (args[++i] != NULL)
	{
		if (!ft_strchr(args[i], '='))
			return (EXIT_SUCCESS);
		var = split_export(args[i], ft_strlen(args[i]));
		if (error_export(var, args[i]) == EXIT_FAILURE)
		{
			if (var)
				double_free(var);
			error = EXIT_FAILURE;
			continue ;
		}
		else if (error_export(var, args[i]) != -2)
			replace_environ(var, args[i]);
		double_free(var);
	}
	return (error);
}

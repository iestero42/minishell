/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/08 11:52:29 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_export_msg(char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
}

static int	error_export(char **var, char *arg)
{
	int	i;

	if (!var)
		error_init("malloc");
	if (arg[0] == '=')
	{
		error_export_msg(arg);
		return (EXIT_FAILURE);
	}
	if (var[0][0] == '_')
		return (-2);
	i = 0;
	while (var[0][i] != '\0')
	{
		if (ft_isalnum(var[0][i]) == 0)
			break ;
		i++;
	}
	if (var[0][i] != '\0')
	{
		error_export_msg(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	replace_environ_aux(char *arg, char ***env)
{
	*env = ft_realloc(*env, arg,
			ft_dstrlen((const char **) *env), 2);
	if (*env == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	replace_environ(char **var, char ***env, char *arg)
{
	char		**env_tmp;

	env_tmp = *env;
	while (*env_tmp != NULL)
	{
		if (!ft_strncmp(*env_tmp, var[0], ft_strlen(var[0]))
			&& (*env_tmp)[strlen(var[0])] == '=')
		{
			if (*env_tmp)
				free(*env_tmp);
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

int	built_export(char **args, char ***env)
{
	int			i;
	char		**var;

	i = 1;
	var = 0;
	while (args[i] != NULL)
	{
		if (!ft_strchr(args[i], '='))
			return (EXIT_SUCCESS);
		var = ft_split(args[i], '=');
		if (error_export(var, args[i]) == EXIT_FAILURE)
		{
			if (var)
				double_free(var);
			return (EXIT_FAILURE);
		}
		if (error_export(var, args[i]) != -2)
			replace_environ(var, env, args[i]);
		double_free(var);
		i++;
	}
	return (EXIT_SUCCESS);
}

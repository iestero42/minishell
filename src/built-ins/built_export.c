/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/28 08:41:32 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_environ_aux(char *arg, char ***env)
{
	*env = ft_realloc(*env, arg,
			ft_dstrlen((const char **) *env), 2);
	if (*env == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	replace_environ(char *arg, char ***env)
{
	char		**env_tmp;
	char		**var;	

	env_tmp = *env;
	var = ft_split(arg, '=');
	if (!var)
		return (EXIT_FAILURE);
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
	double_free(var);
	if (*env_tmp == NULL)
		if (replace_environ_aux(arg, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_export(char **args, char ***env)
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

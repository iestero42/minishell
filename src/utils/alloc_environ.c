/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:37:32 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/18 18:50:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Initializes the environment variables.
 * 
 * @details
 * This function initializes the environment variables for the process. It
 * creates an array of strings, where each string is an environment variable
 * in the format "key=value". The environment variables initialized are PWD,
 * SHLVL, and _.
 * 
 * PWD is set to the current working directory, SHLVL is set to 1, and _ is
 * set to /usr/bin/env. If any memory allocation fails during this process,
 * the function calls error_init with "malloc" as the error message and 1 as
 * the exit status.
 * 
 * @return A pointer to the array of environment variables.
 */
static char	**init_environ(void)
{
	char	**tmp;
	char	*str;
	char	cwd[1024];

	tmp = (char **)malloc(4 * sizeof(char *));
	if (!tmp)
		error_init("malloc", 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		error_init("getcwd", 1);
	str = ft_strdup("PWD=");
	if (!str)
		error_init("malloc", 1);
	str = ft_strjoin(str, cwd);
	tmp[0] = ft_strdup(str);
	free(str);
	tmp[1] = ft_strdup("SHLVL=1");
	tmp[2] = ft_strdup("_=/usr/bin/env");
	tmp[3] = NULL;
	return (tmp);
}

/**
 * @brief 
 * Changes the SHLVL environment variable.
 * 
 * @details
 * This function increments the SHLVL environment variable by 1. SHLVL is an
 * environment variable that tracks the depth of shell nesting. It first
 * converts the current value of SHLVL to an integer, increments it, and then
 * converts it back to a string to store it in the environment array.
 * 
 * @param environ The array of environment variables.
 * @param pos The position of the SHLVL environment variable in the array.
 */
static void	change_shlvl(char **environ, int pos)
{
	int			num;
	char		*str;

	num = ft_atoi(&environ[pos][6]);
	free(environ[pos]);
	environ[pos] = ft_strdup("SHLVL=");
	str = ft_itoa(num + 1);
	environ[pos] = ft_strjoin(environ[pos], str);
	free(str);
}

/**
 * @brief 
 * Allocates memory for the environment variables.
 *
 * @details
 * Duplicates the environment variables and stores them in a new array.
 * The original array of environment variables is then freed.
 * This function is only called once, when the data->access_environ flag is 0.
 *
 * @param data The shell data structure.
 */
void	alloc_environ(t_minishell *data)
{
	char		**tmp;
	extern char	**environ;
	int			i;

	if (data->access_environ == 0)
	{
		if (environ && ft_dstrlen(environ) > 2)
		{
			tmp = ft_dstrdup(environ);
			environ = tmp;
			i = 0;
			while (ft_strncmp("SHLVL", environ[i], 5))
				i++;
			if (!ft_strncmp("SHLVL", environ[i], 5))
				change_shlvl(environ, i);
		}
		else
			environ = init_environ();
		data->access_environ = 1;
	}
}

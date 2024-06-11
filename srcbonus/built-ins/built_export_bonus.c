/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/11 12:03:48 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_export_bonus.c
 * @brief Contains the built_export function for exporting environment variables.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Splits an argument into a variable and its value.
 *
 * @details
 * Allocates memory for a new array of strings.
 * Finds the position of the '=' character in the argument.
 * Creates a substring from the start of the argument to the position 
 * of the '=' character.
 * Duplicates the rest of the argument.
 * Returns the array of strings.
 *
 * @param arg The argument to split.
 * @param len The length of the argument.
 * @return The array of strings.
 */
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

/**
 * @brief 
 * Checks the variable for errors.
 *
 * @details
 * If the variable is NULL, it prints an error message.
 * If the variable starts with '=', is a digit, or has 
 * unclosed quotes, it prints an error message and returns EXIT_FAILURE.
 * If the variable starts with '_', it returns -2.
 * If the variable contains a non-alphanumeric character, 
 * it prints an error message and returns EXIT_FAILURE.
 * Otherwise, it returns EXIT_SUCCESS.
 *
 * @param var The variable to check.
 * @param arg The argument.
 * @return EXIT_SUCCESS, EXIT_FAILURE, or -2.
 */
static int	error_export(char **var, char *arg)
{
	int	i;

	if (!var)
		error_init("malloc", 1);
	if (arg[0] == '=' || ft_isdigit(arg[0]))
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

/**
 * @brief 
 * Reallocates the environment variables array.
 *
 * @details
 * Reallocates the environment variables array with an 
 * additional element for the argument.
 * If the reallocation fails, it returns EXIT_FAILURE.
 * Otherwise, it returns EXIT_SUCCESS.
 *
 * @param arg The argument to add.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
static int	replace_environ_aux(char *arg)
{
	extern char	**environ;
	int			len;

	len = ft_dstrlen(environ);
	environ = ft_realloc(environ, len * sizeof(char *),
			(2 + len) * sizeof(char *));
	environ[len] = ft_strdup(arg);
	environ[len + 1] = NULL;
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Replaces an environment variable.
 *
 * @details
 * Iterates over the environment variables. For each variable, 
 * if the variable starts with the same string as the argument and 
 * the next character is '=', it frees the variable and duplicates 
 * the argument.
 * If the variable is not found, it reallocates the environment 
 * variables array with an additional element for the argument.
 * If the reallocation fails, it returns EXIT_FAILURE.
 * Otherwise, it returns EXIT_SUCCESS.
 *
 * @param var The variable to replace.
 * @param arg The argument.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
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

/**
 * @brief 
 * Exports environment variables.
 *
 * @details
 * Iterates over the arguments. For each argument, if the argument 
 * contains '=', it splits the argument into a variable and its value, 
 * checks the variable for errors, and replaces the environment variable.
 * If the variable check fails, it frees the variable and sets the error 
 * status to EXIT_FAILURE.
 * If the variable check does not return -2, it replaces the 
 * environment variable.
 * 
 *
 * @param args The array of arguments.
 * @return The error status.
 */
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
		var = split_export(args[i], ft_strlen(args[i]));
		if (error_export(var, args[i]) == EXIT_FAILURE)
		{
			if (var)
				double_free(var);
			error = (EXIT_FAILURE << 8);
			continue ;
		}
		else if (error_export(var, args[i]) != -2)
			replace_environ(var, args[i]);
		double_free(var);
	}
	return (error);
}

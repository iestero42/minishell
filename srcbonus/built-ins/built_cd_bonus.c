/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:57:42 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/11 08:48:38 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file built_cd_bonus.c
 * @brief Contains the built_cd function for changing the current directory.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Prints an error message for the `cd` command and returns a failure status.
 *
 * @details
 * This function prints an error message to the standard error file 
 * descriptor. The message includes the name of the shell, the `cd` command, 
 * and the argument that caused the error. If the argument is NULL, it prints 
 * "HOME not set".
 *
 * @param arg The argument that caused the error.
 * @return The exit failure status shifted left by 8 bits.
 */
static int	error_cd_msg(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (arg)
		perror(arg);
	else
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	return (EXIT_FAILURE << 8);
}

/**
 * @brief 
 * Changes the value of an environment variable.
 *
 * @details 
 * This function searches for an environment variable with the given 
 * name and changes its value to the new value. If the variable is found, its 
 * old value is freed and replaced with the new value. If the variable is not 
 * found, the function returns 1.
 *
 * @param varname The name of the environment variable to change.
 * @param newvalue The new value for the environment variable.
 * @param varname_len The length of the variable name.
 * @param newvalue_len The length of the new value.
 * @return 0 if the variable was found and changed, 1 otherwise.
 */
static int	change_env_var(const char *varname, const char *newvalue,
		size_t varname_len, size_t newvalue_len)
{
	extern char	**environ;
	char		*new_entry;
	size_t		new_entry_len;
	size_t		i;

	i = -1;
	while (environ[++i] != NULL)
	{
		if (!ft_strncmp(environ[i], varname, varname_len)
			&& environ[i][varname_len] == '=')
		{
			new_entry_len = varname_len + 1 + newvalue_len + 1;
			new_entry = malloc(sizeof(char) * new_entry_len);
			if (!new_entry)
				error_init("malloc", 1);
			ft_memcpy(new_entry, varname, varname_len);
			new_entry[varname_len] = '=';
			ft_memcpy(new_entry + varname_len + 1, newvalue, newvalue_len);
			new_entry[new_entry_len - 1] = '\0';
			free(environ[i]);
			environ[i] = new_entry;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

/**
 * @brief 
 * Changes the working directory.
 *
 * @details 
 * This function changes the working directory to the directory 
 * specified by `dir`. It also updates the `PWD` and `OLDPWD` environment 
 * variables to reflect the change. If the `OLDPWD` variable does not exist, 
 * it is created.
 *
 * @param dir The directory to change to.
 * @return The exit success status.
 */
static int	change_pwd(char *dir)
{
	extern char	**environ;
	char		*oldpwd;
	char		*tmp;
	int			len;

	oldpwd = getenv("PWD");
	tmp = ft_strdup("OLDPWD=");
	if (change_env_var("OLDPWD", oldpwd, 6, ft_strlen(oldpwd)))
	{
		len = ft_dstrlen(environ);
		environ = ft_realloc(environ, len * sizeof(char *),
				(2 + len) * sizeof(char *));
		environ[len] = ft_strjoin(tmp, oldpwd);
		environ[len + 1] = NULL;
	}
	if (tmp[0] == 'O')
		free(tmp);
	change_env_var("PWD", dir, 3, ft_strlen(dir));
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Changes the current directory.
 *
 * @details
 * If no arguments are provided, it changes the directory to the home directory.
 * If the argument is "~", it changes the directory to the home directory.
 * Otherwise, it changes the directory to the specified directory.
 * If an error occurs, it prints an error message.
 *
 * @param args The array of arguments.
 * @return EXIT_SUCCESS.
 */
int	built_cd(char **args)
{
	int		len;
	char	*dir;
	char	dir_name[1024];

	len = ft_dstrlen(args);
	dir = NULL;
	if (len == 1 || !ft_strcmp(args[1], "~"))
	{
		dir = getenv("HOME");
		if (chdir(dir) != 0)
			return (error_cd_msg(args[1]));
	}
	else
	{
		if (chdir(args[1]) != 0)
			return (error_cd_msg(args[1]));
	}
	getcwd(dir_name, sizeof(dir_name));
	change_pwd(dir_name);
	return (EXIT_SUCCESS);
}

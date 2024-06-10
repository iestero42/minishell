/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/10 08:16:03 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file string_utils2_bonus.c
 * @brief Contains utility functions for strings.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Frees a double pointer.
 *
 * @details
 * Frees each string in the array, then frees the array itself.
 *
 * @param str The double pointer to free.
 */
void	double_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}


/**
 * @brief 
 * Duplicates an array of strings.
 *
 * @details
 * Creates a new array of strings with the same size as the original array.
 * Copies the strings from the original array to the new array.
 *
 * @param str The original array of strings.
 * @return The new array of strings with the copied strings.
 */
char	**ft_dstrdup(char **str)
{
	char	**dup;
	int		i;

	dup = (char **) malloc((ft_dstrlen(str) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

/**
 * @brief Reallocates memory block.
 *
 * @details This function changes the size of the memory block pointed to by 
 * `ptr` to `new_size` bytes. The contents will be unchanged to the minimum 
 * of the old and new sizes; newly allocated memory will be uninitialized. 
 * If `ptr` is NULL, then the call is equivalent to `malloc(new_size)`, for 
 * all values of `new_size`. If `new_size` is equal to zero, and `ptr` is not 
 * NULL, then the call is equivalent to `free(ptr)`. Unless `ptr` is NULL, 
 * it must have been returned by an earlier call to `malloc()`, `calloc()` or 
 * `realloc()`. If the area pointed to was moved, a `free(ptr)` is done.
 *
 * @param ptr Pointer to the memory area to be reallocated.
 * @param old_size Size of the old memory block.
 * @param new_size New size for the memory block.
 * @return Pointer to the newly allocated memory, or NULL if the allocation 
 * failed.
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memset(new_ptr, 0, new_size);
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}


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
	char		*str;
	int			num;

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
			{
				num = ft_atoi(&environ[i][6]);
				free(environ[i]);
				environ[i] = ft_strdup("SHLVL=");
				str = ft_itoa(num + 1);
				environ[i] = ft_strjoin(environ[i], str);
				free(str);
			}
		}
		else
			environ = init_environ();
		data->access_environ = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/29 09:15:48 by yunlovex         ###   ########.fr       */
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

	if (data->access_environ == 0)
	{
		tmp = ft_dstrdup(environ);
		free(environ);
		environ = tmp;
		data->access_environ = 1;
	}
}

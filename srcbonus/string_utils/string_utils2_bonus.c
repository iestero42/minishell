/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 10:20:08 by yunlovex         ###   ########.fr       */
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
 * Copies a substring from a string and appends it to another string.
 *
 * @details
 * Creates a substring from the given string starting from the start index with 
 * the given length. Then appends this substring to the new_token string.
 *
 * @param token The original string.
 * @param new_token The string to append to.
 * @param start The starting index for the substring.
 * @param len The length of the substring.
 * @return The new string with the appended substring.
 */
char	*ft_copy(const char *token, char *new_token, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(token, start + 1, len);
	if (!tmp)
		error_init("malloc", 1);
	new_token = ft_strjoin((char *) new_token, (char *) tmp);
	if (!new_token)
		error_init("malloc", 1);
	free(tmp);
	return (new_token);
}

/**
 * @brief 
 * Appends a string to an array of strings.
 *
 * @details
 * Creates a new array of strings with an additional space for the new string.
 * Copies the strings from the original array to the new array, then adds the 
 * new string to the end.
 *
 * @param arr1 The original array of strings.
 * @param str The string to append.
 * @return The new array of strings with the appended string.
 */
char	**ft_append(char **arr1, char *str)
{
	int		len1;
	int		i;
	char	**combined;

	if (arr1 == NULL)
		len1 = 0;
	else
		len1 = ft_dstrlen(arr1);
	combined = malloc(sizeof(char *) * (len1 + 2));
	if (combined == NULL)
		error_init("malloc", 1);
	i = -1;
	while (++i < len1)
		combined[i] = arr1[i];
	combined[len1] = ft_strdup(str);
	if (!combined[len1])
		error_init("malloc", 1);
	combined[len1 + 1] = NULL;
	free(arr1);
	return (combined);
}

/**
 * Posiblemente esta se borre porque he creado un mejor realloc
 * @brief 
 * Reallocates an array of strings with additional space for a new string.
 *
 * @details
 * Creates a new array of strings with additional space for the new string.
 * Copies the strings from the original array to the new array, then adds 
 * the new string to the end.
 *
 * @param ptr The original array of strings.
 * @param arg The string to append.
 * @param count The number of strings in the original array.
 * @param expand The number of additional spaces for new strings.
 * @return The new array of strings with the appended string.
 */
char	**borrar_futuro(char **ptr, char *arg, int count, int expand)
{
	char	**new_ptr;
	int		i;

	if (ptr == NULL)
		return ((char **) ft_calloc(count + expand, sizeof(char *)));
	new_ptr = (char **) ft_calloc(count + expand, sizeof(char *));
	if (new_ptr == NULL)
		error_init("malloc", 1);
	i = -1;
	while (++i < count)
		new_ptr[i] = ptr[i];
	new_ptr[i] = ft_strdup(arg);
	if (new_ptr[i] == NULL)
		error_init("malloc", 1);
	new_ptr[i + 1] = NULL;
	free(ptr);
	return (new_ptr);
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
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return (new_ptr);
}

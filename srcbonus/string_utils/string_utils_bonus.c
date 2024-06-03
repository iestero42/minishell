/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:05:08 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/29 09:15:27 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file string_utils_bonus.c
 * @brief Contains utility functions for strings.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Compares two strings.
 *
 * @details
 * Compares two strings using ft_strncmp. The length of the longest string 
 * is used as the length parameter.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found, 
 * 	respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s2 = ft_strlen(s2);
	len_s1 = ft_strlen(s1);
	if (len_s1 > len_s2)
		return (ft_strncmp(s1, s2, len_s1));
	else
		return (ft_strncmp(s1, s2, len_s2));
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
 * @brief 
 * Creates a subarray from an array of strings.
 *
 * @details
 * Allocates memory for a new array of strings, then copies a 
 * range of strings from the original array to the new array.
 *
 * @param str_array The original array of strings.
 * @param start_index The start index of the range.
 * @param end_index The end index of the range.
 * @return A pointer to the new array of strings, or NULL if an error occurs.
 */
char	**ft_dsubstr(char **str_array, int start_index, int end_index)
{
	int		num_elements;
	char	**sub_array;
	int		i;

	if (str_array == NULL || start_index < 0 || end_index < start_index)
		return (NULL);
	num_elements = end_index - start_index + 1;
	sub_array = (char **) malloc(sizeof(char *) * (num_elements + 1));
	if (sub_array == NULL)
		return (NULL);
	i = -1;
	while (++i < num_elements)
	{
		sub_array[i] = ft_strdup(str_array[start_index + i]);
		if (sub_array[i] == NULL)
		{
			double_free(sub_array);
			return (NULL);
		}
	}
	sub_array[num_elements] = NULL;
	return (sub_array);
}

/**
 * @brief 
 * Calculates the length of an array of strings.
 *
 * @details
 * Counts the number of strings in the array.
 *
 * @param str The array of strings.
 * @return The number of strings in the array.
 */
int	ft_dstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

/**
 * @brief 
 * Joins two arrays of strings.
 *
 * @details
 * Allocates memory for a new array of strings, then copies the 
 * strings from the first array and the second array to the new array.
 *
 * @param arr1 The first array of strings.
 * @param arr2 The second array of strings.
 * @return A pointer to the new array of strings, or NULL if an error occurs.
 */
char	**ft_dstrjoin(char **arr1, char **arr2)
{
	int		len1;
	int		len2;
	char	**combined;

	if (!arr1)
	{
		arr1 = malloc(sizeof(char *) * 1);
		arr1[0] = NULL;
	}
	if (!arr1 || !arr2)
		return (NULL);
	len1 = ft_dstrlen(arr1);
	len2 = ft_dstrlen(arr2);
	combined = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (combined == NULL)
		return (NULL);
	ft_memcpy(combined, arr1, sizeof(char *) * len1);
	ft_memcpy(combined + len1, arr2, sizeof(char *) * len2);
	combined[len1 + len2] = NULL;
	free(arr1);
	return (combined);
}

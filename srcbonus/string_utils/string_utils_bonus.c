/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:05:08 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:55:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
 * Function that free a double pointer
 * @param str the double pointer to free
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

int	ft_dstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

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

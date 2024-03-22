/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/22 12:11:28 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy(const char *token, char *new_token, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(token, start + 1, len);
	new_token = ft_strjoin((char *) new_token, (char *) tmp);
	free(tmp);
	return (new_token);
}

char	**ft_append(char **arr1, char *str)
{
	int		len1;
	int		i;
	char	**combined;

	if (arr1 == NULL)
		len1 = 0;
	else
		len1 = ft_dstrlen((const char **) arr1);
	combined = malloc(sizeof(char *) * (len1 + 2));
	if (combined == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		combined[i] = arr1[i];
	combined[len1] = ft_strdup(str);
	combined[len1 + 1] = NULL;
	free(arr1);
	return (combined);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

char	**ft_dstrdup(const char **str)
{
	char	**dup;
	int		i;

	dup = (char **) malloc(sizeof(char *) * (ft_dstrlen(str) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (str[i] != NULL)
	{
		dup[i] = (char *) str[i];
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

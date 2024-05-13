/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/08 08:33:32 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

char	**ft_realloc(char **ptr, char *arg, int count, int expand)
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

void	convert_wildcard(char *token, int control)
{
	int	i;

	i = -1;
	if (control == 1)
	{
		while (token[++i] != '\0')
		{
			if (token[i] == '*')
				token[i] = '\1';
		}
	}
	else
	{
		while (token[++i] != '\0')
		{
			if (token[i] == '\1')
				token[i] = '*';
		}
	}
}

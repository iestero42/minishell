/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:31:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 11:28:09 by iestero-         ###   ########.fr       */
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
	int		len2;
	char	**combined;

	len1 = ft_dstrlen((const char **) arr1);
	combined = malloc(sizeof(char *) * (len1 + 2));
	if (combined == NULL)
		return (NULL);
	ft_memcpy(combined, arr1, sizeof(char *) * len1);
	ft_memcpy(combined + len1, str, sizeof(char *) * 1);
	combined[len1 + len2] = NULL;
	free(arr1);
	return (combined);
}

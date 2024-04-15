/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:41:56 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:53:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	**ft_dcopy(const char **token, char **new_token, int start, int len)
{
	char	**tmp;
	char	**result;

	tmp = ft_dsubstr(token, start + 1, len);
	if (!tmp)
		error_init("malloc");
	result = ft_dstrjoin((char *) new_token, (char *) tmp);
	if (!result)
		error_init("malloc");
	double_free(tmp);
	double_free(new_token);
	new_token = result;
	return (new_token);
}

static char	**expand_wildcard(char *token, int *start, int *position)
{
	char	**result;

	result = 0;
	if (token[0] == '*' || !ft_strncmp(&token[ft_strlen(token) - 2], "/*", 2))
		result = expand_directory(token);
	else if (ft_strchr(token, '*') && ft_strchr(token, '/'))
		result = expand_doc(token);
	else
		result = no_expand();
	return (result);
}


char	**parse_wildcard(char **tokens)
{
	int		i;
	int		start;
	char	**result;
	char	**wildcards;

	i = -1;
	start = 0;
	while (tokens[++i] != NULL)
	{
		if (ft_strchr(tokens[i], '*'))
		{
			if (i > start)
				result = ft_dcopy(&tokens[i], result, start - 1, i);
			wildcards = expand_wildcard(tokens[i], &start, &i);
			result = ft_dstrjoin(result, wildcards);
			if (wildcards == NULL)
				double_free(wildcards);
			if (!result)
				error_init("malloc");
		}
	}
	if (start < i && result)
		return (ft_dcopy(&tokens[i], result, start - 1, i));
	return (result);
}

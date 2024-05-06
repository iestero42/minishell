/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:32:07 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_segment(const char *input,
	int *position, int *start, int last_status)
{
	char	*segment;
	char	*segment_expanded;
	char	quote;
	int		i;

	i = *position + 1;
	quote = input[i - 1];
	while (input[i] != quote)
		i++;
	if (i == *position + 1)
		segment = ft_strdup("");
	else
		segment = ft_substr(input, *position + 1, i - *position - 1);
	if (!segment)
		error_init("malloc", 1);
	segment_expanded = parse_env_variable(segment, last_status, quote);
	free(segment);
	*start = i + 1;
	*position = i;
	return (segment_expanded);
}

static char	**ft_copy_expand_aux(char **split, char **new_token)
{
	if (split[0] != NULL && split[0][0] != '\0')
	{
		new_token[ft_dstrlen(new_token) - 1]
			= ft_strjoin(new_token[ft_dstrlen(new_token) - 1], split[0]);
	}
	free(split[0]);
	if (ft_dstrlen(new_token) > 1)
		new_token = ft_dstrjoin(new_token, &split[1]);
	return (new_token);
}

static char	**ft_copy_expand(const char *token, char **new_token,
	int positions[2], int last_status)
{
	char	*tmp;
	char	*tmp_expanded;
	char	**split;

	tmp = ft_substr(token, positions[0] + 1, positions[1]);
	if (!tmp)
		error_init("malloc", 1);
	tmp_expanded = parse_env_variable(tmp, last_status, '\0');
	free(tmp);
	tmp = parse_wildcard(tmp_expanded);
	free(tmp_expanded);
	split = ft_split(tmp, ' ');
	if (!split)
		error_init("malloc", 1);
	if (!new_token)
		new_token = ft_dstrjoin(NULL, split);
	else if (tmp[0] == ' ')
		new_token = ft_dstrjoin(new_token, split);
	else if (tmp[0] != ' ')
		new_token = ft_copy_expand_aux(split, new_token);
	if (!new_token)
		error_init("malloc", 1);
	free(tmp);
	free(split);
	return (new_token);
}

static char	**parse_quotes(char *input, int len, int last_status)
{
	char	**result;
	char	*segment;
	int		i;
	int		start;

	result = 0;
	i = -1;
	start = 0;
	while (++i < len)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (i > start)
				result = ft_copy_expand(input, result,
						(int []){start - 1, i - start}, last_status);
			segment = parse_segment(input, &i, &start, last_status);
			result[ft_dstrlen(result) - 1]
				= ft_strjoin(result[ft_dstrlen(result) - 1], segment);
			free(segment);
			if (!result)
				error_init("malloc", 1);
		}
	}
	return (ft_copy_expand(input, result,
			(int []){start - 1, i - start}, last_status));
}

char	**trim_command(char *token, int last_status)
{
	char	**new_token;

	new_token = parse_quotes(token, ft_strlen(token), last_status);
	if (!new_token && token)
	{
		new_token = (char **) malloc(sizeof(char *) * 2);
		if (!new_token)
			error_init("malloc", 1);
		new_token[0] = ft_strdup(token);
		if (!new_token[0])
		{
			free(new_token);
			return (NULL);
		}
		new_token[1] = NULL;
	}
	return (new_token);
}

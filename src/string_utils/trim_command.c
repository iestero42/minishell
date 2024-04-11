/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/11 09:38:42 by iestero-         ###   ########.fr       */
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
		error_init("malloc");
	segment_expanded = parse_env_variable(segment, last_status, quote);
	free(segment);
	*start = i + 1;
	*position = i;
	return (segment_expanded);
}

static char	*ft_copy_expand(const char *token, char *new_token,
	int positions[2], int last_status)
{
	char	*tmp;
	char	*tmp_expanded;

	tmp = ft_substr(token, positions[0] + 1, positions[1]);
	if (!tmp)
		error_init("malloc");
	tmp_expanded = parse_env_variable(tmp, last_status, '\0');
	free(tmp);
	new_token = ft_strjoin((char *) new_token, (char *) tmp_expanded);
	if (!new_token)
		error_init("malloc");
	free(tmp_expanded);
	return (new_token);
}

static char	*parse_quotes(char *input, int len, int last_status)
{
	char	*result;
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
			result = ft_strjoin(result,
					parse_segment(input, &i, &start, last_status));
			if (!result)
				error_init("malloc");
		}
	}
	return (ft_copy_expand(input, result,
			(int []){start - 1, i - start}, last_status));
}

char	*trim_command(char *token, int last_status)
{
	char	*new_token;

	new_token = parse_quotes(token, ft_strlen(token), last_status);
	if (!new_token && token)
		return (ft_strdup(token));
	return (new_token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 11:40:12 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_segment(const char *input,
	int *position, int *start)
{
	char	*segment;
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
	*start = i + 1;
	*position = i;
	return (segment);
}

static char	*parse_quotes(char *input, int len)
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
				result = ft_copy(input, result, start - 1, i - start);
			result = ft_strjoin(result,
					parse_segment(input, &i, &start));
			if (!result)
				return (NULL);
		}
	}
	if (start < i && result)
		return (ft_copy(input, result, start - 1, i - start));
	return (result);
}

char	*trim_command(char *token)
{
	char	*new_token;

	new_token = parse_quotes(token, ft_strlen(token));
	if (!new_token)
		return (token);
	free(token);
	token = new_token;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/04 09:02:01 by iestero-         ###   ########.fr       */
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
				result = ft_copy(input, result, start + 1, i - start);
			result = ft_strjoin(result,
					parse_segment(input, &i, &start));
			if (!result)
				return (NULL);
		}
	}
	if (start < i && result)
		return (ft_copy(input, result, start + 1, i - start - 1));
	return (input);
}

int	trim_command(char **tokens)
{
	int		i;
	char	*new_token;

	i = -1;
	while (tokens[++i] != NULL)
	{
		new_token = parse_quotes(tokens[i], ft_strlen(tokens[i]));
		if (!new_token)
			return (EXIT_FAILURE);
		tokens[i] = new_token;
	}
	return (EXIT_SUCCESS);
}

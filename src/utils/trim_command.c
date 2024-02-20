/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/20 12:22:03 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_segment(char *result, const char *input,
	int *position, int *start)
{
	char	;
}

static char	*parse_quotes(const char *input, size_t len)
{
	char	*result;
	int		i;
	int		start;

	result = (char *) malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	start = 0;
	while (++i < len)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (i > start)
				result = ft_copy(input, result, start + 1, i - start);
			result = parse_segment(result, input, &i, &start);
		}
	}
	if (start < i && result)
		result = ft_copy(input, result, start + 1, i - start - 1);
	return (result);
}

int	trim_command(char **tokens)
{
	int		i;
	char	*new_token;

	i = 0;
	while (tokens[i] != NULL)
	{
		new_token = remove_quote_pairs(tokens[i], ft_strlen(tokens[i]));
		if (!new_token)
			return (NULL);
		tokens[i] = new_token;
		free(new_token);
	}
	return (EXIT_SUCCESS);
}
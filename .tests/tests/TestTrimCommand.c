/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestTrimCommand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:29:43 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 09:55:00 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_segment(char *result, const char *input,
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

static char	*parse_quotes(const char *input, size_t len)
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
					parse_segment(result, input, &i, &start));
			if (!result)
				return (NULL);
		}
	}
	if (start < i && result)
		result = ft_copy(input, result, start - 1, i - start);
	return (result);
}

int main(void)
{
	char	*s;
	char	*input;

	printf("Test 1: \"hola\"\"hola\" \n\n");
	input = "\"hola\"\"hola\"";
	s = parse_quotes("\"hola\"\"hola\"", ft_strlen(input));
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 2: \"\"hola\"\"hola\"\" \n\n");
	input = "\"\"hola\"\"hola\"\"";
	s = parse_quotes(input, ft_strlen(input));
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 3: \"\'hola\'\"\"hola\"hola \n\n");
	input = "\"\'hola\'\"\"hola\"hola";
	s = parse_quotes(input, ft_strlen(input));
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 4: adios\'\"hola\"\'\"hola\" \n\n");
	input = "adios\'\"hola\"\'\"hola\"";
	s = parse_quotes(input, ft_strlen(input));
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	return (0);
}

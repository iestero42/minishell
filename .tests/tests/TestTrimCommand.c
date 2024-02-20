/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestTrimCommand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:29:43 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/20 11:46:49 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quote_pairs(const char *input, size_t len)
{
	char	*result;
	int		index;
	int		i;

	if (input == NULL)
		return (NULL);
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	index = 0;
	i = -1;
	while (++i < len)
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (input[i - 1] != input[i] || input[i + 1] == input[i])
				i++;
			else
				result[index++] = input[i];
		}
		else
			result[index++] = input[i];
	}
	result[index] = '\0';
	return (result);
}

int main(void)
{
	char	*s;

	s = remove_quote_pairs("\"hola\"\"hola\"", ft_strlen("\"hola\"\"hola\""));
	printf("-- string: %s -- \n", s);
	free(s);
}

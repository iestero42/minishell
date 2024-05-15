/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:17:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/15 08:44:15 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	convert_wildcard(char *token, char chr, char ctrl, int control)
{
	int	i;

	i = -1;
	if (control == 1)
	{
		while (token[++i] != '\0')
		{
			if (token[i] == chr)
				token[i] = ctrl;
		}
	}
	else
	{
		while (token[++i] != '\0')
		{
			if (token[i] == ctrl)
				token[i] = chr;
		}
	}
}

void	reconvert_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		convert_wildcard(tokens[i], '\0', '\4', 0);
		convert_wildcard(tokens[i], '<', '\2', 0);
		convert_wildcard(tokens[i], '>', '\3', 0);
        i++;
	}
}

void	remove_parenthesis(char **tokens)
{
	int	i;
	int	j;
	int	count_parentheses;

	i = -1;
	j = 0;
	count_parentheses = 0;
	while (tokens[++i] != NULL)
	{
		if (*tokens[i] == '(')
		{
			count_parentheses++;
			if (count_parentheses == 1)
				tokens[j++] = tokens[i] + 1;
		}
		else if (*tokens[i] == ')')
		{
			count_parentheses--;
			if (count_parentheses == 0)
				tokens[j++] = tokens[i] + 1;
		}
		else
			tokens[j++] = tokens[i];
	}
	tokens[j] = NULL;
}

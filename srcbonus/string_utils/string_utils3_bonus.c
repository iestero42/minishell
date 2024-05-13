/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:17:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 11:21:59 by iestero-         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:17:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:40:01 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	convert_char(char *token, char chr, char ctrl, int control)
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

void	convert_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		convert_char(tokens[i], '\0', ENVP_VAR, 0);
		convert_char(tokens[i], '<', INPUT_REDIR, 0);
		convert_char(tokens[i], '>', OUTPUT_REDIR, 0);
		i++;
	}
}

void	remove_parenthesis(char **tokens)
{
	int	i;
	int	j;
	int	count_parentheses;

	j = 0;
	if (*tokens[0] == '(' && *tokens[ft_dstrlen(tokens) - 1] == ')')
	{
		i = 0;
		count_parentheses = 1;
		while (tokens[++i] != NULL)
		{
			if (*tokens[i] == '(')
				count_parentheses++;
			else if (*tokens[i] == ')')
				count_parentheses--;
			if (count_parentheses != 0)
				tokens[j++] = tokens[i];
			if (count_parentheses == 0)
				tokens[j++] = NULL;
		}
	}
}

void	alloc_environ(t_minishell *data)
{
	char		**tmp;
	extern char	**environ;

	if (data->access_environ == 0)
	{
		tmp = ft_dstrdup(environ);
		free(environ);
		environ = tmp;
		data->access_environ = 1;
	}
}

void	convert_token(char *tokens)
{
	convert_char(tokens, '*', WILDCARD, 1);
	convert_char(tokens, '<', INPUT_REDIR, 1);
	convert_char(tokens, '>', OUTPUT_REDIR, 1);
}

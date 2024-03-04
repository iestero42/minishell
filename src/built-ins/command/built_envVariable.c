/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_envVariable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:24:02 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/04 08:45:42 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*special_env_variable(int last_status)
{
	char	*str;

	str = ft_itoa(last_status);
	if (!str)
		return (NULL);
	return (str);
}

static char	*expand_env_variable(char *token, int *start, int *position,
	int last_status)
{
	int		i;
	char	*str;
	char	*env_var;

	if (token[0] == '?')
	{
		i = *position;
		*position = i + 1;
		*start = *position;
		return (special_env_variable(last_status));
	}
	i = 0;
	while (token[i] != '\0' && ft_isalnum(token[i]))
		i++;
	str = ft_substr(token, 0, i);
	if (str == NULL)
		return (NULL);
	env_var = getenv(str);
	if (!env_var)
		return (ft_strdup(""));
	free(str);
	*position += i;
	*start = *position;
	return (env_var);
}

static char	*check_token(char *token, int last_status)
{
	char	*new_token;
	int		i;
	int		start;

	i = -1;
	start = 0;
	new_token = 0;
	while (token[++i] != '\0')
	{
		if (token[i] == '$')
		{
			if (i > start)
				new_token = ft_copy(token, new_token, start + 1, i - start);
			new_token = ft_strjoin(new_token,
					expand_env_variable(&token[i] + 1, &start, &i,
						last_status));
			if (!new_token)
				return (NULL);
		}
	}
	if (start < i && new_token)
		return (ft_copy(token, new_token, start + 1, i - start - 1));
	return (token);
}

int	built_env_variable(char **tokens, int last_status)
{
	int		i;
	char	*new_token;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i][0] == '\'')
			return (EXIT_SUCCESS);
		else
		{
			new_token = check_token(tokens[i], last_status);
			tokens[i] = new_token;
		}
	}
	return (EXIT_SUCCESS);
}

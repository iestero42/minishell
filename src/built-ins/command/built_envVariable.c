/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_envVariable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:24:02 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/14 09:25:54 by iestero-         ###   ########.fr       */
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

	i = -1;
	if (token[0] == '?')
	{
		i = *position;
		*position = i + 1;
		*start = *position;
		return (special_env_variable(last_status));
	}
	while (token[i] != '\0' && ft_isalnum(token[i]))
		i++;
	str = ft_substr(token, 0, i + 1);
	if (str == NULL)
		return (NULL);
	env_var = getenv(str);
	free(str);
	*position += i;
	*start = *position;
	return (env_var);
}

static int	check_token(char *token, int last_status)
{
	char	*new_token;
	char	*tmp;
	int		i;
	int		start;

	i = -1;
	start = 0;
	new_token = 0;
	while (token[++i] != '\0')
	{
		if (token[i] == '$')
		{
			tmp = ft_substr(token, start, i);
			new_token = ft_strjoin(new_token, tmp);
			free(tmp);
			tmp = expand_env_variable(&token[i] + 1, &start, &i, last_status);
			new_token = ft_strjoin(new_token, tmp);
			free(tmp);
			if (!new_token)
				return (EXIT_FAILURE);
		}
	}
	if (start < i && new_token)
		token = ft_strjoin(new_token, &token[i]);
	return (EXIT_SUCCESS);
}

int	built_env_variable(char **tokens, int last_status)
{
	int	i;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i][0] == '\'')
			return (EXIT_SUCCESS);
		else
			if (check_token(tokens[i], last_status) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

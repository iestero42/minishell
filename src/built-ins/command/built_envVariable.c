/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_envVariable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:24:02 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/11 12:52:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_variable(char *token, int start, int position)
{
	int		i;
	char	*str;
	char	*env_var;

	i = -1;
	while (token[i] != '\0' && ft_isalnum(token[i]))
		i++;
	str = ft_substr(token, 0, i + 1);
	if (str == NULL)
		return (NULL);
	env_var = getenv(str);
	free(str);
	return (env_var);
}

static int	check_inside_token(char *token)
{
	int		i;
	char	*env_var;
	char	*new_token;

	i = -1;
	new_token = NULL;
	while (token[++i] != '\0')
	{
		if (token[i] == '$')
		{
			new_token = ft_substr(token, 0, i);
			if (!new_token)
				return (EXIT_FAILURE);
			env_var = expand_env_variable(&token[i] + 1);
			new_token = ft_strjoin(new_token, env_var);
			if (!new_token)
				return (EXIT_FAILURE);
		}
	}
	if (new_token)
		token = new_token;
	return (EXIT_SUCCESS);
}

static int	check_token(char *token)
{
	char	*new_token;
	char	*substr;
	char	*env_var;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			substr = ft_substr(token, start, i + 1);
			if (!substr)
				return (EXIT_FAILURE);
			new_token = ft_strjoin(new_token, substr);
			free(substr);
			env_var = expand_env_variable(&token[i] + 1, &start, &i);
			if (!env_var)
				return (EXIT_FAILURE);
			new_token = ft_strjoin(new_token, env_var);
			free(env_var);
		}
	}
	if (start < i)
	{
		new_token = ft_strjoin(new_token, &token + i);
	}
	return (EXIT_SUCCESS);
}

int	built_env_variable(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i][0] == '\'')
			return (EXIT_SUCCESS);
		else if (tokens[i][0] == '"')
			if (check_inside_token_quotes(tokens[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		else
			if (check_token(tokens[i])
				== EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

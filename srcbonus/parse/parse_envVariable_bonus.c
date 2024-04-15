/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envVariable_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:24:02 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:40:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*special_env_variable(int last_status, int *position,
	int *start)
{
	char	*str;
	int		i;

	i = *position;
	*position = i + 1;
	*start = *position + 1;
	str = ft_itoa(last_status);
	if (!str)
		error_init("malloc");
	return (str);
}

static char	*expand_env_variable(char *token, int *start, int *position,
	int last_status)
{
	int		i;
	char	*str;
	char	*env_var;

	if (token[0] == '?')
		return (special_env_variable(last_status, position, start));
	i = 0;
	while (token[i] != '\0' && ft_isalnum(token[i]))
		i++;
	str = ft_substr(token, 0, i);
	if (str == NULL)
		error_init("malloc");
	env_var = getenv(str);
	if (!env_var)
		env_var = ft_strdup("");
	if (env_var == NULL)
		error_init("malloc");
	free(str);
	*position += i;
	*start = *position + 1;
	return (env_var);
}

static char	*check_token(char *token, int last_status)
{
	char	*new_token;
	char	*env;
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
				new_token = ft_copy(token, new_token, start - 1, i - start);
			env = expand_env_variable(&token[i] + 1, &start, &i, last_status);
			new_token = ft_strjoin(new_token, env);
			if (*env == '\0')
				free(env);
			if (!new_token)
				error_init("malloc");
		}
	}
	if (start < i && new_token)
		return (ft_copy(token, new_token, start - 1, i - start));
	return (new_token);
}

char	*parse_env_variable(char *token, int last_status, int quote)
{
	char	*new_token;

	if (token == NULL)
		return (NULL);
	if (quote == '\'')
		return (ft_strdup(token));
	else
	{
		new_token = check_token(token, last_status);
		if (new_token == NULL)
			new_token = ft_strdup(token);
	}
	return (new_token);
}

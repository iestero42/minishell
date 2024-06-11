/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envVariable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:24:02 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/11 09:03:58 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_envVariable_bonus.c
 * @brief Contains the functions for parsing environment variables.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Handles special environment variables.
 *
 * @details
 * Converts the last status to a string and updates 
 * the position and start indices.
 *
 * @param last_status The last status of the command.
 * @param position The current position in the token.
 * @param start The start index of the environment variable in the token.
 * @return The string representation of the last status.
 */
static char	*special_env_variable(int last_status, int *position,
	int *start)
{
	char	*str;
	int		i;

	i = *position;
	*position = i + 1;
	*start = *position + 1;
	last_status = (last_status >> 8) & 0xFF;
	str = ft_itoa(last_status);
	if (!str)
		error_init("malloc", 1);
	return (str);
}

/**
 * @brief 
 * Expands an environment variable in a token.
 *
 * @details
 * If the token is a special environment variable, it calls special_env_variable.
 * Otherwise, it extracts the environment variable name, gets its value,
 * and updates the position and start indices.
 *
 * @param token The token to expand.
 * @param start The start index of the environment variable in the token.
 * @param position The current position in the token.
 * @param last_status The last status of the command.
 * @return The value of the environment variable.
 */
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
		error_init("malloc", 1);
	env_var = getenv(str);
	if (!env_var)
		env_var = ft_strdup("\5");
	if (env_var == NULL)
		error_init("malloc", 1);
	free(str);
	*position += i;
	*start = *position + 1;
	return (ft_strdup(env_var));
}

/**
 * @brief 
 * Checks a token for environment variables.
 *
 * @details
 * Iterates over the token. If it finds a '$', it expands 
 * the environment variable and appends it to the new token.
 *
 * @param token The token to check.
 * @param last_status The last status of the command.
 * @return The new token with expanded environment variables.
 */
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
			free(env);
			if (!new_token)
				error_init("malloc", 1);
		}
	}
	if (start < i && new_token)
		return (ft_copy(token, new_token, start - 1, i - start));
	return (new_token);
}

/**
 * @brief 
 * Parses an environment variable in a token.
 *
 * @details
 * If the token is NULL, it returns NULL. If the quote is a single quote,
 * it returns a copy of the token. Otherwise, it checks the token 
 * for environment variables.
 *
 * @param token The token to parse.
 * @param last_status The last status of the command.
 * @param quote The quote character.
 * @return The parsed token.
 */
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

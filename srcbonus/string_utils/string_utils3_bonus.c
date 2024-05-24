/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:17:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:37:24 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file string_utils3_bonus.c
 * @brief Contains utility functions for string conversion.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Converts characters in a string.
 *
 * @details
 * Iterates over the characters in a string. If a character matches the chr 
 * parameter, it is replaced with the ctrl parameter. If the control parameter 
 * is 1, the function operates in reverse: if a character matches the ctrl 
 * parameter, it is replaced with the chr parameter.
 *
 * @param token The string to convert.
 * @param chr The character to replace.
 * @param ctrl The replacement character.
 * @param control The control parameter.
 */
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

/**
 * @brief 
 * Converts characters in an array of strings.
 *
 * @details
 * Iterates over the strings in an array. For each string, it replaces certain 
 * characters with control characters. The '\0' character is replaced with the 
 * ENVP_VAR control character, the '<' character is replaced with the 
 * INPUT_REDIR control character, and the '>' character is replaced with 
 * the OUTPUT_REDIR control character.
 *
 * @param tokens The array of strings to convert.
 */
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

/**
 * @brief 
 * Removes parentheses from an array of strings.
 *
 * @details
 * Iterates over the strings in an array. If a string is a 
 * parenthesis, it is removed from the array. The function only 
 * removes the outermost parentheses.
 *
 * @param tokens The array of strings to remove parentheses from.
 */
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

/**
 * @brief 
 * Allocates memory for the environment variables.
 *
 * @details
 * Duplicates the environment variables and stores them in a new array.
 * The original array of environment variables is then freed.
 * This function is only called once, when the data->access_environ flag is 0.
 *
 * @param data The shell data structure.
 */
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

/**
 * @brief 
 * Converts characters in a string.
 *
 * @details
 * Replaces certain characters in a string with control characters.
 * The '*' character is replaced with the WILDCARD control character,
 * the '<' character is replaced with the INPUT_REDIR control character,
 * and the '>' character is replaced with the OUTPUT_REDIR control character.
 *
 * @param tokens The string to convert.
 */
void	convert_token(char *tokens)
{
	convert_char(tokens, '*', WILDCARD, 1);
	convert_char(tokens, '<', INPUT_REDIR, 1);
	convert_char(tokens, '>', OUTPUT_REDIR, 1);
}

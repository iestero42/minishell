/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:17:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/18 18:50:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file string_utils3_bonus.c
 * @brief Contains utility functions for string conversion.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

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

/**
 * @brief 
 * Copies a substring from a string and appends it to another string.
 *
 * @details
 * Creates a substring from the given string starting from the start index with 
 * the given length. Then appends this substring to the new_token string.
 *
 * @param token The original string.
 * @param new_token The string to append to.
 * @param start The starting index for the substring.
 * @param len The length of the substring.
 * @return The new string with the appended substring.
 */
char	*ft_copy(const char *token, char *new_token, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(token, start + 1, len);
	if (!tmp)
		error_init("malloc", 1);
	new_token = ft_strjoin((char *) new_token, (char *) tmp);
	if (!new_token)
		error_init("malloc", 1);
	free(tmp);
	return (new_token);
}

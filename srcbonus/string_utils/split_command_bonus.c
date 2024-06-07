/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:03:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/07 07:55:38 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file split_command_bonus.c
 * @brief Contains the functions for splitting commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

static char	**alloc_subtrings(char **substrings)
{
	int	len;

	len = ft_dstrlen(substrings);
	substrings = ft_realloc(substrings, sizeof(char *) * (len + 1),
			sizeof(char *) * (len + 2));
	if (!substrings)
		error_init("malloc", 1);
	return (substrings);
}

/**
 * @brief 
 * Handles errors in split operands.
 *
 * @details
 * Prints an error message if there are unclosed quotes or unexpected '&' tokens.
 *
 * @param count The number of operands.
 * @param quotes The quote status.
 * @return The number of operands, or -2 if there is an error.
 */
static void	*error_split_command(int mode)
{
	if (mode == 1)
		ft_putstr_fd("minishell: syntax error near 'newline'\n", STDERR_FILENO);
	else if (mode == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token '&'\n",
			STDERR_FILENO);
	return (NULL);
}

/**
 * @brief 
 * Allocates memory for a substring.
 *
 * @details
 * Allocates memory for a substring of a given length, 
 * and copies the substring into the allocated memory.
 * The start position is updated to the end of the substring.
 *
 * @param s The string to allocate memory from.
 * @param len The length of the substring.
 * @param start The starting position in the string.
 * @return A pointer to the allocated memory, or NULL 
 * 	if an error occurs.
 */
static char	*save_memory(const char *s, size_t len, int *start)
{
	char	*substr;

	if (s[0] == '<' || s[0] == '>' || s[0] == '|'
		|| s[0] == '&' || s[0] == '(' || s[0] == ')')
	{
		if (s[0] == s[1] && s[0] != '(' && s[0] != ')')
			len = 2;
		else
			len = 1;
	}
	if (s[0] == '&' && s[1] != '&')
		return (error_split_command(2));
	*start = *start + len;
	substr = (char *) malloc(sizeof(char) * (len + 2));
	if (!substr)
		error_init("malloc", 1);
	ft_strlcpy(substr, (char *) s, len + 1);
	return (substr);
}

/**
 * @brief 
 * Gets the next substring in a string.
 *
 * @details
 * Finds the next substring in a string, starting from a given position.
 * A substring is a sequence of characters that are not spaces or 
 * special characters, or a sequence of characters enclosed in quotes.
 *
 * @param start The starting position in the string.
 * @param s The string to get the substring from.
 * @return A pointer to the substring, or NULL if an error occurs.
 */
static char	*get_next_substring(int *start, const char *s)
{
	const char	*start_chr;
	char		in_quotes;
	int			i;

	in_quotes = UNQUOTED;
	while (s[*start] == ' ')
		*start = *start + 1;
	start_chr = &s[*start];
	i = -1;
	while (start_chr[++i] && (in_quotes || (start_chr[i] != ' '
				&& start_chr[i] != '<' && start_chr[i] != '>'
				&& start_chr[i] != '(' && start_chr[i] != ')'
				&& start_chr[i] != '&' && start_chr[i] != '|')))
	{
		if ((start_chr[i] == '"' || start_chr[i] == '\'') && !in_quotes)
			in_quotes = start_chr[i];
		else if (start_chr[i] == in_quotes && in_quotes)
			in_quotes = UNQUOTED;
	}
	if (in_quotes)
		return (error_split_command(1));
	return (save_memory(start_chr, i, start));
}

/**
 * @brief 
 * Splits a command into substrings.
 *
 * @details
 * Splits a command into substrings. A substring is a sequence of 
 * characters that are not spaces or special characters, or a 
 * sequence of characters enclosed 
 * in quotes. The substrings are stored in an array.
 *
 * @param s The command to split.
 * @return An array of substrings, or NULL if an error occurs.
 */
char	**split_command(const char *s, int len_s)
{
	char		**substrings;
	int			start;
	int			len;
	int			i;

	substrings = (char **) ft_calloc(1, sizeof(char *));
	if (!substrings)
		error_init("malloc", 1);
	start = 0;
	i = 0;
	while (start < len_s)
	{
		substrings = alloc_subtrings(substrings);
		substrings[i] = get_next_substring(&start, s);
		if (substrings[i++] == NULL)
		{
			double_free(substrings);
			return (NULL);
		}
	}
	substrings[i] = NULL;
	return (substrings);
}

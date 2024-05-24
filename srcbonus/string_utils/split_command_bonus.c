/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:03:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:37:48 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file split_command_bonus.c
 * @brief Contains the functions for splitting commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Calculates the size of the next substring in a string.
 *
 * @details
 * Counts the number of characters in the next substring in a string, 
 * starting from a given position. The position is updated to the end of 
 * the substring.
 *
 * @param count The current count of characters.
 * @param s The string to calculate the size from.
 * @param position The starting position in the string.
 * @return The updated count of characters, or -2 if an error occurs.
 */
static int	size_aux(int count, const char *s, int *position)
{
	int		i;

	count++;
	i = *position;
	if (s[i] != ')' && s[i] != '(' && s[i] == s[i + 1])
	{
		if (s[i] == s[i + 1] && (s[i - 1] == ' ' || i == 0))
			i = i + 2;
		else if (s[i] == s[i + 1] && s[i - 1] != ' ' && s[i] != ' ')
			i++;
	}
	else if (s[i] == '&' && s[i] != s[i + 1])
		return (-2);
	else if (s[i - 1] == ' ' || i == 0)
		i = i + 1;
	while (s[i] == ' ')
		i++;
	if ((*position == 0 || s[*position] == ' ' || s[*position - 1] == ' ')
		&& s[*position + 1] != '\0')
		*position = i - 1;
	else
		*position = i;
	return (count);
}

/**
 * @brief 
 * Calculates the number of substrings in a string.
 *
 * @details
 * Counts the number of substrings in a string. A substring is a 
 * sequence of characters that are not spaces or special characters, or a 
 * sequence of characters enclosed in quotes.
 *
 * @param s The string to calculate the size from.
 * @return The number of substrings in the string, or -2 if an error occurs.
 */
static int	size_dstr(const char *s)
{
	int		count;
	int		i;
	char	in_quotes;

	count = 0;
	in_quotes = UNQUOTED;
	i = -1;
	while (s[++i] != '\0' && count >= 0)
	{
		if ((s[i] == '"' || s[i] == '\'') && !in_quotes)
			in_quotes = s[i];
		else if (in_quotes == s[i] && in_quotes)
		{
			in_quotes = UNQUOTED;
			count++;
		}
		else if ((s[i] == ' ' || s[i + 1] == '\0'
				|| s[i] == '<' || s[i] == '>'
				|| s[i] == ')' || s[i] == '('
				|| s[i] == '&' || s[i] == '|') && !in_quotes)
			count = size_aux(count, s, &i);
	}
	return (error_split_operands(count, in_quotes));
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
	*start = *start + len;
	substr = (char *) malloc(sizeof(char) * (len + 2));
	if (!substr)
		return (NULL);
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
		return (NULL);
	return (save_memory(start_chr, i, start));
}

/**
 * @brief 
 * Splits a command into substrings.
 *
 * @details
 * Splits a command into substrings. A substring is a sequence of characters
 * that are not spaces or special characters, or a sequence of characters enclosed 
 * in quotes. The substrings are stored in an array.
 *
 * @param s The command to split.
 * @return An array of substrings, or NULL if an error occurs.
 */
char	**split_command(const char *s)
{
	int			num_substrings;
	char		**substrings;
	int			start;
	int			i;

	num_substrings = size_dstr(s);
	if (num_substrings == -2)
		return (NULL);
	substrings = malloc(sizeof(char *) * (num_substrings + 1));
	if (!substrings)
		error_init("malloc", 1);
	start = 0;
	i = -1;
	while (++i < num_substrings)
	{
		substrings[i] = get_next_substring(&start, s);
		if (substrings[i] == NULL)
		{
			double_free(substrings);
			error_init("malloc", 1);
		}
	}
	substrings[num_substrings] = NULL;
	return (substrings);
}

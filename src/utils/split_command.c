/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:30:38 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/13 11:44:46 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
static int	size_dstr(const char *s)
{
	int		count;
	int		i;
	int		in_quotes;
	char	current_quote;

	count = 0;
	in_quotes = UNQUOTED;
	current_quote = '\0';
	i = -1;
	while (s[++i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && !in_quotes)
		{
			in_quotes = QUOTED;
			current_quote = s[i];
		}
		else if (s[i] == current_quote && in_quotes)
		{
			in_quotes = UNQUOTED;
			count++;
		}
		else if ((s[i] == ' ' || s[i + 1] == '\0') && !in_quotes)
			count++;
	}
	return (count);
}

static char	*save_memory(const char *s, size_t len)
{
	char	*substr;

	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *) s, len + 1);
	substr[len] = '\0';
	return (substr);
}

/**
 * @brief Get the next substring object
 * 
 * @param s 
 * @return char* 
 */
static char	*get_next_substring(int *start, const char *s)
{
	const char	*start_chr;
	int			in_quotes;
	int			i;

	start_chr = &s[*start];
	in_quotes = UNQUOTED;
	while (*start_chr == ' ')
		start_chr++;
	i = 0;
	while (start_chr[i] && (in_quotes || start_chr[i] != ' '))
	{
		if ((start_chr[i] == '"' || start_chr[i] == '\'') && !in_quotes)
			in_quotes = QUOTED;
		else if ((start_chr[i] == '"' || start_chr[i] == '\'') && in_quotes)
		{
			in_quotes = UNQUOTED;
			break ;
		}
		i++;
	}
	if (in_quotes)
		return (NULL);
	*start = *start + i + 1;
	return (save_memory(start_chr, i + 1));
}

/**
 * @brief 
 * 
 * @param s 
 * @return char** 
 */
char	**split_command(const char *s)
{
	int			num_substrings;
	char		**substrings;
	int			start;
	int			i;

	if (s == NULL)
		return (NULL);
	num_substrings = size_dstr(s);
	substrings = malloc(sizeof(char *) * (num_substrings + 1));
	if (!substrings)
		return (NULL);
	start = 0;
	i = -1;
	while (++i < num_substrings)
	{
		substrings[i] = get_next_substring(&start, s);
		if (substrings[i] == NULL)
		{
			double_free(substrings);
			return (NULL);
		}
	}
	substrings[num_substrings] = NULL;
	return (substrings);
}

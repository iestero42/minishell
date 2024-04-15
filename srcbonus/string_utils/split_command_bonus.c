/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:03:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:40:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	size_aux(int count, const char *s, int *position)
{
	int		i;

	count++;
	i = *position;
	if (s[i] == '<' || s[i] == '>' || s[i] == ' ')
	{
		if (s[i] == s[i + 1] && (s[i - 1] == ' ' || i == 0))
			i = i + 2;
		else if (s[i] == s[i + 1] && s[i - 1] != ' ' && s[i] != ' ')
			i++;
		else if (s[i - 1] == ' ')
			i = i + 1;
		while (s[i] == ' ')
			i++;
	}
	if ((s[*position] == ' ' || s[*position - 1] == ' ' || *position == 0)
		&& s[*position + 1] != '\0')
		*position = i - 1;
	else
		*position = i;
	return (count);
}

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
	char	in_quotes;

	count = 0;
	in_quotes = UNQUOTED;
	i = -1;
	while (s[++i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && !in_quotes)
			in_quotes = s[i];
		else if (in_quotes == s[i] && in_quotes)
		{
			in_quotes = UNQUOTED;
			count++;
		}
		else if ((s[i] == ' ' || s[i + 1] == '\0'
				|| s[i] == '<' || s[i] == '>') && !in_quotes)
			count = size_aux(count, s, &i);
	}
	if (in_quotes)
		return (-2);
	return (count);
}

static char	*save_memory(const char *s, size_t len, int *start)
{
	char	*substr;

	if (s[0] == '<' || s[0] == '>')
	{
		if (s[0] == s[1])
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
 * @brief Get the next substring object
 * 
 * @param s 
 * @return char* 
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
				&& start_chr[i] != '<' && start_chr[i] != '>')))
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
		error_init("malloc");
	start = 0;
	i = -1;
	while (++i < num_substrings)
	{
		substrings[i] = get_next_substring(&start, s);
		if (substrings[i] == NULL)
		{
			double_free(substrings);
			error_init("malloc");
		}
	}
	substrings[num_substrings] = NULL;
	return (substrings);
}

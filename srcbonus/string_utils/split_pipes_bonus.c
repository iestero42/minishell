/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:30:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/09 10:20:54 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	error_split(int count, int quotes, const char *s)
{
	int	len;

	len = ft_strlen(s);
	if (quotes)
	{
		ft_putstr_fd("minishell: syntax error near 'newline'\n", 2);
		return (-2);
	}
	else if (len > 0 && s[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (-2);
	}
	else if (len > 0 && count == 0)
		return (1);
	return (count);
}

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
static int	size_dstr(char *s)
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
			in_quotes = UNQUOTED;
		if ((s[i] == '|' || s[i + 1] == '\0') && !in_quotes)
		{
			if (s[i + 1] == '|' && i++)
				continue ;
			if (s[i] == '|')
				s[i] = '\2';
			count++;
		}
	}
	return (error_split(count, in_quotes, s));
}

static char	*save_memory(const char *s, size_t len)
{
	char	*substr;

	if (len == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (NULL);
	}
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		error_init("malloc", 1);
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
	i = 0;
	while (start_chr[i] && (in_quotes || start_chr[i] != '\2'))
	{
		if ((start_chr[i] == '"' || start_chr[i] == '\'') && !in_quotes)
			in_quotes = start_chr[i];
		else if (in_quotes == start_chr[i] && in_quotes)
			in_quotes = UNQUOTED;
		i++;
	}
	*start = *start + i + 1;
	return (save_memory(start_chr, i));
}

/**
 * @brief 
 * 
 * @param s 
 * @return char** 
 */
char	**split_pipes(char *s)
{
	int			num_substrings;
	char		**substrings;
	int			start;
	int			i;

	num_substrings = size_dstr(s);
	if (num_substrings == 0 || num_substrings == -2)
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
			return (NULL);
		}
	}
	substrings[num_substrings] = NULL;
	return (substrings);
}

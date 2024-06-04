/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/04 08:55:06 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file trim_command_bonus.c
 * @brief Contains functions for trimming and expanding commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Parses a segment of the input string.
 *
 * @details
 * A segment is a part of the input string that is enclosed in quotes.
 * The function finds the end of the segment, creates a substring, and 
 * expands any environment variables in the substring.
 *
 * @param input The input string.
 * @param position The current position in the input string.
 * @param start The start of the segment.
 * @param last_status The last status of the shell.
 * @return The expanded segment.
 */
static char	*parse_segment(const char *input,
	int *position, int *start, int last_status)
{
	char	*segment;
	char	*segment_expanded;
	char	quote;
	int		i;

	i = *position + 1;
	quote = input[i - 1];
	while (input[i] != quote)
		i++;
	if (i == *position + 1)
		segment = ft_strdup("");
	else
		segment = ft_substr(input, *position + 1, i - *position - 1);
	if (!segment)
		error_init("malloc9", 1);
	segment_expanded = parse_env_variable(segment, last_status, quote);
	free(segment);
	*start = i + 1;
	*position = i;
	return (segment_expanded);
}

/**
 * @brief 
 * Copies and expands a string.
 *
 * @details
 * The function splits the string at spaces, then joins the split strings 
 * to the new_token array. If the first character of the string is not a space, 
 * the first split string is joined to the last string in the new_token array.
 *
 * @param split The split strings.
 * @param new_token The array of strings to join to.
 * @return The new array of strings.
 */
static char	**ft_copy_expand_aux(char **split, char **new_token)
{
	if (split[0] != NULL && split[0][0] != '\0')
	{
		new_token[ft_dstrlen(new_token) - 1]
			= ft_strjoin(new_token[ft_dstrlen(new_token) - 1], split[0]);
	}
	free(split[0]);
	if (ft_dstrlen(split) > 1)
		new_token = ft_dstrjoin(new_token, &split[1]);
	return (new_token);
}

/**
 * @brief 
 * Copies and expands a segment of the input string.
 *
 * @details
 * The function creates a substring from the input string, expands any 
 * environment variables in the substring, and converts certain characters to 
 * control characters. The expanded substring is then split at spaces and 
 * joined to the new_token array.
 *
 * @param token The input string.
 * @param new_token The array of strings to join to.
 * @param positions The start and end of the segment.
 * @param last_status The last status of the shell.
 * @return The new array of strings.
 */
static char	**ft_copy_expand(const char *token, char **new_token,
	int positions[2], int last_status)
{
	char	*tmp;
	char	*tmp_expanded;
	char	**split;

	tmp = ft_substr(token, positions[0] + 1, positions[1]);
	if (!tmp)
		error_init("malloc6", 1);
	tmp_expanded = parse_env_variable(tmp, last_status, '\0');
	convert_token(tmp_expanded);
	free(tmp);
	split = ft_split(tmp_expanded, ' ');
	if (!split)
		error_init("malloc7", 1);
	if (!new_token)
		new_token = ft_dstrjoin(new_token, split);
	else if (tmp_expanded[0] == ' ')
		new_token = ft_dstrjoin(new_token, split);
	else if (tmp_expanded[0] != ' ')
		new_token = ft_copy_expand_aux(split, new_token);
	if (!new_token)
		error_init("malloc8", 1);
	free(tmp_expanded);
	free(split);
	return (new_token);
}

/**
 * @brief 
 * Parses the input string for quoted segments.
 *
 * @details
 * The function iterates over the characters in the input string.
 * When it encounters a quote, it copies and expands the segment 
 * of the string before the quote, then parses the quoted segment.
 * The expanded segments are joined to the result array.
 *
 * @param input The input string.
 * @param len The length of the input string.
 * @param last_status The last status of the shell.
 * @return The array of expanded segments.
 */
static char	**parse_quotes(char *input, int len, int last_status)
{
	char	**result;
	char	*segment;
	int		i;
	int		start;

	result = 0;
	i = -1;
	start = 0;
	while (++i < len)
	{
		if (input[i] != '"' && input[i] != '\'')
			continue ;
		if (i > start)
			result = ft_copy_expand(input, result,
					(int []){start - 1, i - start}, last_status);
		segment = parse_segment(input, &i, &start, last_status);
		if (!result)
			result = ft_dstrdup(&segment);
		else
			result[ft_dstrlen(result) - 1]
				= ft_strjoin(result[ft_dstrlen(result) - 1], segment);
		free(segment);
	}
	return (ft_copy_expand(input, result,
			(int []){start - 1, i - start}, last_status));
}

/**
 * @brief 
 * Trims and expands a command.
 *
 * @details
 * The function parses the command for quoted segments and 
 * expands any environment variables. If the command does not contain 
 * any quotes, it is duplicated and added to the new_token array. 
 * The command is then parsed for wildcard characters and expanded 
 * if any are found.
 *
 * @param token The command.
 * @param last_status The last status of the shell.
 * @return The array of expanded segments.
 */
char	**trim_command(char *token, int last_status)
{
	char	**new_token;
	char	**tmp;

	new_token = parse_quotes(token, ft_strlen(token), last_status);
	if (!new_token && token)
	{
		new_token = (char **) malloc(sizeof(char *) * 2);
		if (!new_token)
			error_init("malloc5", 1);
		new_token[0] = ft_strdup(token);
		if (!new_token[0])
		{
			free(new_token);
			return (NULL);
		}
		new_token[1] = NULL;
	}
	tmp = parse_wildcard(new_token);
	if (tmp)
	{
		double_free(new_token);
		new_token = tmp;
	}
	return (new_token);
}

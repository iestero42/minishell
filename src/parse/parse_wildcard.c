/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/25 10:11:32 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_wildcard_bonus.c
 * @brief Contains the functions for parsing wildcards.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

/**
 * @brief 
 * Matches a pattern with a string.
 *
 * @details
 * Recursively matches a pattern with a string. The pattern can contain '\1' 
 * characters, which match any character in the string.
 *
 * @param pattern The pattern to match.
 * @param str The string to match.
 * @return 1 if the pattern matches the string, 0 otherwise.
 */
static int	wildcard_match_str(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '\1' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == *str)
		return (wildcard_match_str(pattern + 1, str + 1));
	if (*pattern == '\1')
		return (wildcard_match_str(pattern + 1, str)
			|| wildcard_match_str(pattern, str + 1));
	return (0);
}

/**
 * @brief 
 * Finds directory entries that match a token.
 *
 * @details
 * Reads directory entries from a directory. If an entry matches 
 * the token, it appends it to a string.
 *
 * @param dir The directory to read from.
 * @param token The token to match.
 * @return A string containing the matching directory entries, 
 * 	separated by '\2' characters.
 */
static char	*matching_dir_content(DIR *dir, const char *token)
{
	struct dirent	*ent;
	struct stat		path_stat;
	char			*ret;

	ret = NULL;
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (ent->d_name[0] != '.')
		{
			stat(ent->d_name, &path_stat);
			if (wildcard_match_str(token, ent->d_name))
			{
				if (ret)
					ret = ft_strjoin(ret, "\2");
				ret = ft_strjoin(ret, ent->d_name);
			}
		}
		ent = readdir(dir);
	}
	return (ret);
}

/**
 * @brief 
 * Expands a wildcard.
 *
 * @details
 * Opens the current directory and finds entries that match the token. 
 * The token can contain wildcards, which are expanded to matching 
 * directory entries.
 *
 * @param token The token to expand.
 * @return A string containing the expanded wildcard, or NULL if 
 * 	the token is NULL.
 */
static char	*expand_wildcard(const char *token)
{
	DIR		*dir;
	char	*ret;

	ret = NULL;
	if (token == NULL)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		perror("opendir_wildcard");
	else
	{
		ret = matching_dir_content(dir, token);
		closedir(dir);
	}
	return (ret);
}

/**
 * @brief 
 * Parses wildcards in tokens.
 *
 * @details
 * Iterates over the tokens. If a token contains a wildcard, it expands 
 * it to matching directory entries. Then, it splits the expanded wildcard 
 * into separate tokens.
 *
 * @param token The tokens to parse.
 * @return A new array of tokens, with wildcards expanded.
 */
char	**parse_wildcard(char **token)
{
	char	**new_token;
	char	*expand;
	char	**split;
	int		i;

	if (!token)
		return (NULL);
	new_token = NULL;
	i = -1;
	while (token[++i] != NULL && ft_strchr(token[i], WILDCARD))
	{
		expand = NULL;
		expand = expand_wildcard(token[i]);
		if (expand == NULL)
			expand = ft_strdup(token[i]);
		convert_char(expand, '*', WILDCARD, 0);
		split = ft_split(expand, '\2');
		free(expand);
		if (split == NULL)
			error_init("malloc", 1);
		new_token = ft_dstrjoin(new_token, split);
		free(split);
	}
	return (new_token);
}

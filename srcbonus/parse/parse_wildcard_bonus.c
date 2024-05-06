/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:41:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wildcard_match_str(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == '?' || *pattern == *str)
		return (wildcard_match_str(pattern + 1, str + 1));
	if (*pattern == '*')
		return (wildcard_match_str(pattern + 1, str)
			|| wildcard_match_str(pattern, str + 1));
	return (0);
}

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
			if ((path_stat.st_mode & 0100000)
				&& wildcard_match_str(token, ent->d_name))
			{
				if (ret)
					ret = ft_strjoin(ret, " ");
				ret = ft_strjoin(ret, ent->d_name);
			}
		}
		ent = readdir(dir);
	}
	return (ret);
}

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

char	*parse_wildcard(char *token)
{
	char	*new_token;

	if (token == NULL)
		return (NULL);
	if (!ft_strchr(token, '*') && !ft_strchr(token, '?'))
		return (ft_strdup(token));
	else
	{
		new_token = expand_wildcard(token);
		if (new_token == NULL)
			new_token = ft_strdup(token);
	}
	return (new_token);
}

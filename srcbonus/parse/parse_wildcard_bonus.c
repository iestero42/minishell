/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/07 12:09:02 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

char	**parse_wildcard(char **token)
{
	char	**new_token;
	char	*expand;
	char	**split;
	int		i;

	if (token == NULL)
		return (NULL);
	i = -1;
	new_token = NULL;
	while (token[++i] != NULL)
	{
		if (!ft_strchr(token[i], '\1'))
			new_token = ft_dstrjoin(new_token, &token[i]);
		else
		{
			expand = expand_wildcard(token[i]);
			if (expand == NULL)
			{
				expand = ft_strdup(token[i]);
				convert_wildcard(expand, 0);
			}
			split = ft_split(expand, '\2');
			free(expand);
			if (split == NULL)
				error_init("malloc", 1);
			else
				new_token = ft_dstrjoin(new_token, split);
			free(split);
		}
	}
	return (new_token);
}

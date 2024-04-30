/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:53:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/18 11:58:38 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		wildcard_match_str(const char *pattern, const char *str)
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
    DIR             *dir;
	char	        *ret;
	
	ret = NULL;
	if (token == NULL)
		return (NULL);
	dir = opendir(".");
    if (!dir)
	{
        /* could not open directory */
        perror("opendir_wildcard");
    }
	ret = matching_dir_content(dir, token);
	closedir(dir);
	return (ret);
}
/*
char	*expand_wildcard(const char *token, int *start, int *position)
{
    DIR             *dir;
    struct dirent   *ent;
	struct stat     path_stat;
	char	        *ret;
	
	ret = NULL;
	if (token == NULL)
		return (NULL);
	dir = opendir(".");
    if (dir != NULL)
	{
        / print all the files and directories within directory /
		ent = readdir(dir);
        while (ent != NULL)
		{
			if (ent->d_name[0] != '.')
			{
				stat(ent->d_name, &path_stat);
				if (path_stat.st_mode & 0100000)
				{
					if (ret)
						ret = ft_strjoin(ret, " ");
					ret = ft_strjoin(ret, ent->d_name);
				}
			}
			ent = readdir(dir);
		}
        closedir(dir);
        *start += ft_strlen(ret);
        *position += ft_strlen(ret);
        ret = ft_strjoin(ret, token + 1);
    }
	else
	{
        / could not open directory /
        perror("opendir_wildcard");
    }
	return (ret);
}
*/
/*
static char	*check_token(char *token)
{
	char	*new_token;
	char	*env;
	int		i;
	int		start;

	i = -1;
	start = 0;
	new_token = NULL;
	while (token[++i] != '\0')
	{
		if (ft_strchr(token, '*'))
		{
			if (i > start)
				new_token = ft_copy(token, new_token, start - 1, i - start);
			env = expand_wildcard(&token[i] + 1, &start, &i);
			new_token = ft_strjoin(new_token, env);
			if (*env == '\0')
				free(env);
			if (!new_token)
				error_init("malloc", 1);
		}
	}
	if (start < i && new_token)
		return (ft_copy(token, new_token, start - 1, i - start));
	return (new_token);
}
*/
char	*parse_wildcard(char *token)
{
	if (token == NULL)
		return (NULL);
	if (!ft_strchr(token, '*'))
		return (ft_strdup(token));
	return (expand_wildcard(token));
}

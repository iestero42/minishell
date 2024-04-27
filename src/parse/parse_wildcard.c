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
        /* print all the files and directories within directory */
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
        /* could not open directory */
        perror("opendir_wildcard");
    }
	return (ret);
}

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
		if (token[i] == '*')
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

char	*parse_wildcard(char *token, int quote)
{
	char	*new_token;

	if (token == NULL)
		return (NULL);
	if (quote == '\'')
		return (ft_strdup(token));
	else
	{
		new_token = check_token(token);
		if (new_token == NULL)
			new_token = ft_strdup(token);
	}
	return (new_token);
}

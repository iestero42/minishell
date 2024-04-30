/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:41:56 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:53:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	**ft_dcopy(const char **token, char **new_token, int start, int len)
{
	char	**tmp;
	char	**result;

	tmp = ft_dsubstr(token, start + 1, len);
	if (!tmp)
		error_init("malloc");
	result = ft_dstrjoin(new_token, tmp);
	if (!result)
		error_init("malloc");
	double_free(tmp);
	double_free(new_token);
	new_token = result;
	return (new_token);
}

char	**expand_directory(const char *dir_name)
{
    DIR		*dir;
    struct	dirent *entry;
    struct	stat entry_stat;
    char	path[1024];
	char	**result;

	printf("EXPAND_DIRECTORY***************\n");
	result = NULL;
    dir = opendir(dir_name);
    if (!dir) {
        perror("opendir");
        return (NULL);
    }

    while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break;
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        if (stat(path, &entry_stat) == -1) {
            perror("stat");
            continue;
        }
        if (S_ISDIR(entry_stat.st_mode)) {
            printf("%s is a directory\n", entry->d_name);
        } else if (S_ISREG(entry_stat.st_mode)) {
            printf("%s is a regular file\n", entry->d_name);
        } else {
            printf("%s is of unknown type\n", entry->d_name);
        }
    }
	printf("***************\n\n");
    closedir(dir);
	return (result);
}

char	**expand_doc(const char *dir_name)
{
	char	**result;

	printf("EXPAND_DOC %s ***************\n", dir_name);
	result = NULL;
	return (result);
}

static char	**expand_wildcard(char *token, int *start, int *position)
{
	char	**result;
	char	path[1024];

	printf("Start: %d, Position: %d\n", *start, *position);
	result = NULL;
	getcwd(path, sizeof(path));
	ft_strjoin(path, "/");
	if (token[0] == '*' || !ft_strncmp(&token[ft_strlen(token) - 2], "/*", 2))
		result = expand_directory(path);
	else if (ft_strchr(token, '*') && ft_strchr(token, '/'))
		result = expand_doc(path);
	else
		result = NULL; /*no_expand();*/
	return (result);
}


char	**parse_wildcard(char **tokens)
{
	int		i;
	int		start;
	char	**result;
	char	**wildcards;

	i = -1;
	start = 0;
	while (tokens[++i] != NULL)
	{
		if ('*' == tokens[i][0]))/****************SEGUIR AQUÍ*/
		{
			wildcards = expand_wildcard(tokens[i]);
			if (i > start)
				result = ft_dcopy(&tokens[i], result, start - 1, i);
			result = ft_dstrjoin(result, wildcards);
			if (wildcards == NULL)
				double_free(wildcards);
			if (!result)
				error_init("malloc");
		}
	}
	if (start < i && result)
		return (ft_dcopy(&tokens[i], result, start - 1, i));
	return (result);
}

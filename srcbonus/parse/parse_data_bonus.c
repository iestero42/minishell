/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 10:14:43 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_data_bonus.c
 * @brief Contains the function for parsing data.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

int	ends_with(const char *str, const char *suffix)
{
    size_t	lenstr;
    size_t	lensuffix;
    
	if (!str || !suffix)
		return 0;
	lenstr = ft_strlen(str);
	lensuffix = ft_strlen(suffix);
	if (lensuffix > lenstr)
		return 0;
	return (ft_strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0);
}

int	has_unclosed_parenthesis(const char *str)
{
    int			count;
    int			in_quote;
    const char	*p;

	count = 0;
	in_quote = UNQUOTED;
	p = str;
    while (*p)
    {
        if ((*p == '\'' || *p == '"') && !in_quote)
            in_quote = *p;
        else if (*p == in_quote && in_quote)
            in_quote = UNQUOTED;
        else if (*p == '(' && !in_quote)
            count++;
        else if (*p == ')' && !in_quote)
            count--;
        ++p;
    }
    return (count < 0);
}

int	ends_with_and_or_pipe(const char *str)
{
	return (ends_with(str, "&&") || ends_with(str, "||") || ends_with(str, "|"));
}

char	*read_complete_command(void)
{
    char	*line;
    size_t	len;
    char	*complete_line;

	printf("> ");
	line = get_next_line(STDIN_FILENO);
    len = strlen(line);
	complete_line = malloc(len + 1);
	ft_strlcpy(complete_line, line, len + 1);
    free(line);
	while (ends_with_and_or_pipe(complete_line) || has_unclosed_parenthesis(complete_line))
	{
        printf("> ");
        line = get_next_line(STDIN_FILENO);
        len = ft_strlen(complete_line) + ft_strlen(line);
        complete_line = ft_realloc(complete_line, ft_strlen(complete_line) * sizeof(char),
			(len + 1) * sizeof(char));
        ft_strlcat(complete_line, line, len + 1);
        free(line);
    }

    return (complete_line);
}

/**
 * @brief 
 * Parses the command line data.
 *
 * @details
 * This function trims the command line, checks if it's empty, and if not,
 * parses the command and returns the result.
 *
 * @param command_line The command line to parse.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure or 
 * 	if the command line is empty.
 */
int	parse_data(char *command_line, t_minishell *data)
{
	char	*tmp;
	int		result;

	g_signal = 0;
	tmp = ft_strtrim(command_line, " ");
	if (!tmp)
		error_init("ft_strtrim", 1);
	if (*tmp == '\0')
	{
		free(tmp);
		return (EXIT_FAILURE);
	}
	result = parse_command(tmp, data);
	free(tmp);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:27:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/27 08:46:27 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ends_with_and_or_pipe(char **tokens)
{
	int	len;
    
	if (!tokens)
		return 0;
    len = ft_dstrlen(tokens);
    if (len > 1 && (*tokens[len - 1] == '&' || *tokens[len - 1] == '|'))
		return (1);
	return (0);
}

static int	has_unclosed_parenthesis(char **tokens)
{
    int count;
    int i;

	count = 0;
	i = -1;
    while (tokens[++i] != NULL)
    {
        if (*tokens[i] == '(')
            count++;
        else if (*tokens[i] == ')') 
            count--;
    }
    return (count > 0);
}

static char **read_complete_command(char **command_line)
{
    char	*line;
    char    *tmp;
    char    **tokens;

	while (ends_with_and_or_pipe(command_line) || has_unclosed_parenthesis(command_line))
	{
        line = readline_own("> ");
        if (*line != '\0')
        {
            tmp = ft_strtrim(line, "\n ");
            if (!tmp)
                error_init("malloc", 1);
            tokens = split_command(tmp);
            if (!tokens)
                error_init("malloc", 1);
            command_line = ft_dstrjoin(command_line, tokens);
            free(line);
            free(tmp);
            free(tokens);
        }
    }
    return (command_line);
}

/**
 * @brief 
 * Handles parenthesis errors.
 *hide_eof_symbol(&term);
 * @details
 * This function iterates over the tokens and checks for an uneven number of open 
 * and closed parentheses, an open parenthesis that is not preceded by a '&' or '|', 
 * or a '&' or '|' that is not correctly placed.
 * If any of these errors are found, an error message is printed and EXIT_FAILURE 
 * is returned. If no errors
 * are found, EXIT_SUCCESS is returned.
 *
 * @param tokens An array of char pointers containing the input tokens.
 * @return Returns EXIT_FAILURE if a parenthesis error is found, and 
 * 	EXIT_SUCCESS otherwise.
 */
char	**check_err_sintax(char **tokens)
{
	int	i;
	int	count_parentheses;

	i = -1;
	count_parentheses = 0;
	while (tokens[++i] != NULL)
	{
		if (*tokens[i] == ')')
			count_parentheses--;
		if (*tokens[i] == '(' && ++count_parentheses
			&& (i > 0 && *tokens[i - 1] !=  '&' && *tokens[i - 1] != '|'))
			return (print_estd(tokens, 1, i));
		if (count_parentheses < 0 || (*tokens[i] == '('
			&& tokens[i + 1] != NULL && *tokens[i + 1] == ')'))
			return (print_estd(tokens, 2, i));
		if (((*tokens[i] == '&' || *tokens[i] == '|') && (i == 0
			|| (tokens[i + 1] != NULL && (*tokens[i + 1] == '&'
			|| *tokens[i + 1] == '|')))) || (*tokens[i] == ')'
			&& tokens[i + 1] != NULL && (*tokens[i + 1] != '|'
			&& *tokens[i + 1] != '&')))
			return (print_estd(tokens, 3, i));
		if (tokens[i + 1] == NULL && ((count_parentheses > 0) || (count_parentheses == 0
			&& (*tokens[i] == '&' || *tokens[i] == '|'))))
			tokens = read_complete_command(tokens);
	}
	return (tokens);
}
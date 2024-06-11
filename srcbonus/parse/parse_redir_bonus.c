/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:21:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/11 12:21:02 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_redir_bonus.c
 * @brief Contains the functions for parsing redirections.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Checks if a token contains only '\5' characters.
 *
 * @details
 * Counts the number of '\5' characters and other characters in the token.
 * If the token contains only '\5' characters or no '\5' characters, 
 * it returns 1. Otherwise, it returns 0.
 *
 * @param token The token to check.
 * @return 1 if the token contains only '\5' characters or no '\5' 
 * 	characters, 0 otherwise.
 */
static int	check_slash5(char *token)
{
	int	i;
	int	slash5_count;
	int	other_count;

	slash5_count = 0;
	other_count = 0;
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '\5')
			slash5_count++;
		else
			other_count++;
	}
	if ((slash5_count > 0 && other_count == 0) || slash5_count == 0)
		return (1);
	else
		return (0);
}

/**
 * @brief 
 * Removes '\5' characters from a token.
 *
 * @details
 * Iterates over the token. If it finds a '\5' character, 
 * it removes it from the token.
 *
 * @param token The token to modify.
 * @return The modified token.
 */
static char	*remove_char(char *token)
{
	char	*tmp;
	char	*before;
	char	*after;
	int		j;

	tmp = token;
	j = 0;
	while (tmp[j] != '\0')
	{
		if (tmp[j] == '\5')
		{
			before = ft_substr(token, 0, j);
			after = ft_substr(token, j + 1, ft_strlen(token) - j - 1);
			tmp = ft_strjoin(before, after);
			free(after);
			j = 0;
		}
		else
			j++;
	}
	return (tmp);
}

/**
 * @brief 
 * Removes '\5' characters from tokens.
 *
 * @details
 * Iterates over the tokens. If a token contains '\5' characters,
 * it removes them.
 *
 * @param token The tokens to modify.
 */
static void	rm_slash5(char **token)
{
	int		i;

	i = 0;
	while (token[i] != NULL)
	{
		if (!check_slash5(token[i]) && ft_strlen(token[i]) > 1)
			token[i] = remove_char(token[i]);
		i++;
	}
}

/**
 * @brief 
 * Parses the redirections in the tokens.
 *
 * @details
 * Removes '\5' characters from the tokens, then parses 
 * the output and input redirections.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to modify.
 * @param control The control character.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	parse_redirect(char **tokens, t_command *cmd, char *control,
		t_minishell *data)
{
	int	i;

	i = -1;
	rm_slash5(tokens);
	while (tokens[++i] != NULL && data->status != STOPPED)
	{
		if (parse_output(&tokens[i], cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (parse_input(&tokens[i], cmd, control, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

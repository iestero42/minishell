/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:36:06 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file misc_bonus.c
 * @brief Contains miscellaneous functions.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Writes a character to the standard output.
 *
 * @param c The character to write.
 * @return The number of bytes written.
 */
int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

/**
 * @brief 
 * Reads a line from the standard input.
 *
 * @details
 * Prints a prompt, reads a line from the standard input, 
 * and appends a space to the line if it ends with a newline.
 *
 * @return The line read from the standard input.
 */
char	*readline_own(void)
{
	char	*line;

	ft_putstr_fd("> ", 1);
	line = get_next_line(STDIN_FILENO);
	if (*line == '\n')
	{
		line = ft_strjoin(line, " ");
	}
	return (line);
}

/**
 * @brief 
 * Assigns an operand to a tree node.
 *
 * @details
 * If the token is '||', assigns SEMICOLON.
 * If the token is '&', assigns AND.
 * Otherwise, assigns PIPE.
 *
 * @param tokens The array of tokens.
 * @param tree The tree node.
 * @param i The current position in the array.
 */
void	assign_operand(char **tokens, t_tree *tree, int i)
{
	if (tokens[i][0] == '|' && tokens[i][1] == '|')
		tree->number = SEMICOLON;
	else if (tokens[i][0] == '&')
		tree->number = AND;
	else
		tree->number = PIPE;
}

/**
 * @brief 
 * Checks for a new command in the tokens.
 *
 * @details
 * Iterates over the tokens until it finds a '|' or '&' token at the top level 
 * of parentheses, or a ')' token followed by a token that is not '|' or '&'.
 * If it finds an error in the parentheses, it returns EXIT_FAILURE.
 * Otherwise, it sets the position to the index of the found token and returns 
 * EXIT_SUCCESS.
 *
 * @param pos The position to set.
 * @param tokens The array of tokens.
 * @return EXIT_SUCCESS if a new command is found, otherwise EXIT_FAILURE.
 */
int	check_new_command(int *pos, char **tokens)
{
	int	count_parentheses;
	int	i;

	count_parentheses = 0;
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (*tokens[i] == '(')
			count_parentheses++;
		if (*tokens[i] == ')')
			count_parentheses--;
		if ((count_parentheses == 0 && (*tokens[i] == '|' || *tokens[i] == '&'))
			|| (*tokens[i] == ')' && (*tokens[i + 1] != '|'
					&& *tokens[i + 1] != '&')))
			break ;
	}
	if (error_parenthesis(count_parentheses, tokens, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*pos = i;
	return (EXIT_SUCCESS);
}

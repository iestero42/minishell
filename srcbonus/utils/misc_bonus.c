/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/27 12:45:23 by iestero-         ###   ########.fr       */
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
 * @param prompt The prompt to print.
 *
 * @return The line read from the standard input.
 */
char	*readline_own(char *prompt, int fd)
{
	char	*line;

	ft_putstr_fd(prompt, 1);
	line = get_next_line(fd);
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
 * 
*/
char	**print_estd(char **tokens, int mode, int i)
{
	if (mode == 1)
        ft_putstr_fd("minishell: syntax error near unexpected token '('\n", 2);
    if (mode == 2)
        ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
    if (mode == 3)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(tokens[i + 1], 2);
        ft_putstr_fd("'\n", 2);
    }
	double_free(tokens);
	return (NULL);
}

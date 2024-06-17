/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/17 08:31:34 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file misc_bonus.c
 * @brief Contains miscellaneous functions.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

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
 * @brief Prints syntax error messages and frees tokens.
 *
 * @details This function prints different syntax error messages based on the 
 * mode provided. It then frees the memory allocated for the tokens array and 
 * returns NULL.
 *
 * @param tokens The tokens array to be freed.
 * @param mode The mode to determine which error message to print.
 * @param i The index of the token causing the error.
 * @return NULL after freeing the tokens array.
 */
char	**print_estd(char **tokens, int mode, int i, t_minishell *data)
{
	if (mode == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token '('\n",
			STDERR_FILENO);
	if (mode == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n",
			STDERR_FILENO);
	if (mode == 3)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tokens[i], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	if (mode == 4)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tokens[i + 1], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	data->last_status_cmd = (2 << 8);
	double_free(tokens);
	return (NULL);
}

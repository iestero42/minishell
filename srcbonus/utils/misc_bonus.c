/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:21:08 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

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

void	assign_operand(char **tokens, t_tree *tree, int i)
{
	if (tokens[i][0] == '|' && tokens[i][1] == '|')
		tree->number = SEMICOLON;
	else if (tokens[i][0] == '&')
		tree->number = AND;
	else
		tree->number = PIPE;
}

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

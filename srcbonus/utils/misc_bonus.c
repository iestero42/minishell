/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 08:39:06 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	print_exit(void)
{
	printf("exit\n");
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

char	*readline_main(void)
{
	return (readline(MINISHELL_ENTRY));
}

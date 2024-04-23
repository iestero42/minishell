/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 13:06:47 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	print_exit(void)
{
	tputs(tgetstr("up", NULL), 1, ft_putchar);
	printf("%s", MINISHELL_ENTRY);
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

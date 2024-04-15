/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 16:23:51 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	print_exit(void)
{
	tputs(tgetstr("up", NULL), 1, ft_putchar);
	printf("minishell~$ exit\n");
}

char	*readline_own(void)
{
	ft_putstr_fd("> ", 1);
	return (get_next_line(STDIN_FILENO));
}

char	*readline_main(void)
{
	ft_putchar_fd('\r', 1);
	return (readline("minishell~$ "));
}

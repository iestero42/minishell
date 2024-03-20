/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:39 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/20 11:37:33 by iestero-         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/26 09:01:53 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_title(void)
{
	printf(LINE_1, BLUE, RESET);
	printf(LINE_2, BLUE, RESET, BLUE, RESET);
	printf(LINE_3, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_4, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_5, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_6, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_7, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_8, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_9, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_10, BLUE, RESET, BLUE, RESET);
	printf(LINE_11, BLUE, RESET);
}

static int	minishell(void)
{
	return 1;
}

int	main(void)
{
	t_minishell	data;

	show_title();
	data.stat = RUNNING;
	while (data.stat != STOPPED)
	{
		parse_data(readline(MINISHELL_ENTRY), &data);
		minishell();
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:55:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 09:51:43 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hide_eof_symbol(struct termios *term)
{

	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term->c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	configurations(void)
{
	struct termios	term;

	hide_eof_symbol(&term);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:55:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/19 12:33:50 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hide_eof_symbol(struct termios *term)
{

	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	cfmakeraw(term);
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	configurations(void)
{
	struct termios	term;

	hide_eof_symbol(&term);
}

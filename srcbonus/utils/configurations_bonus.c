/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurations_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:55:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 12:48:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	show_title(void)
{
	printf(LINE_1, BLUE, RESET);
	printf(LINE_2, BLUE, RESET, BLUE, RESET);
	printf(LINE_3, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_4, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_5, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_6, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_7, BLUE, YELLOW, BLUE, RESET);
	printf(LINE_8, BLUE, RESET);
}

void	hide_eof_symbol(struct termios *term)
{
	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term->c_lflag |= 0001000;
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	show_eof_symbol(struct termios *term)
{
	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	init(t_minishell *data)
{
	struct termios	term;

	show_title();
	data->status = RUNNING;
	data->std_fileno[1] = dup(STDOUT_FILENO);
	if (data->std_fileno[1] < 0)
		error_init("dup", 1);
	data->std_fileno[0] = dup(STDIN_FILENO);
	if (data->std_fileno[0] < 0)
		error_init("dup", 1);
	data->cmd_list[0] = "echo";
	data->cmd_list[1] = "cd";
	data->cmd_list[2] = "pwd";
	data->cmd_list[3] = "export";
	data->cmd_list[4] = "unset";
	data->cmd_list[5] = "env";
	data->cmd_list[6] = "exit";
	data->access_environ = 0;
	data->last_status_cmd = 0;
	if (tcgetattr(STDIN_FILENO, &data->original_term) == -1)
		error_init("tcgetattr", 1);
	hide_eof_symbol(&term);
	signal(SIGQUIT, SIG_IGN);
}

void	deinit(t_minishell *data)
{
	extern char	**environ;

	if (data->access_environ == 1)
		double_free(environ);
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_term);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurations_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:55:57 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/14 07:15:56 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file configurations_bonus.c
 * @brief Contains functions for configuring the shell.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Displays the shell title.
 *
 * @details
 * Prints the shell title using printf. The title is defined by the 
 * LINE_1 to LINE_8 macros.
 */
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

/**
 * @brief 
 * Hides the EOF symbol.
 *
 * @details
 * Modifies the terminal settings to hide the EOF symbol.
 *
 * @param term The terminal settings.
 */
void	hide_eof_symbol(void)
{
	struct termios	*term;

	term = (struct termios *) malloc(sizeof(struct termios));
	if (term == NULL)
		error_init("malloc", 1);
	ft_memset(term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	free(term);
}

/**
 * @brief 
 * Shows the EOF symbol.
 *
 * @details
 * Modifies the terminal settings to show the EOF symbol.
 *
 * @param term The terminal settings.
 */
void	show_eof_symbol(void)
{
	struct termios	*term;

	term = (struct termios *) malloc(sizeof(struct termios));
	if (term == NULL)
		error_init("malloc", 1);
	ft_memset(term, 0, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	free(term);
}

/**
 * @brief 
 * Initializes the shell.
 *
 * @details
 * Displays the shell title, sets the shell status to RUNNING, 
 * duplicates the standard input and output file descriptors,
 * initializes the command list, and hides the EOF symbol.
 *
 * @param data The shell data structure.
 */
void	init(t_minishell *data)
{
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
	data->n_line = 1;
	if (tcgetattr(STDIN_FILENO, &data->original_term) == -1)
		error_init("tcgetattr", 1);
	hide_eof_symbol();
	signal(SIGQUIT, signal_free_environ);
}

/**
 * @brief 
 * Deinitializes the shell.
 *
 * @details
 * Frees the environment variables, clears the command history, 
 * and restores the original terminal settings.
 *
 * @param data The shell data structure.
 */
void	deinit(t_minishell *data)
{
	extern char	**environ;

	if (data->access_environ == 1)
		double_free(environ);
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_term);
}

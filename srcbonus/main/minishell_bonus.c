/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/27 16:13:15 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minishell_bonus.c
 * @brief Main entry point for the minishell program.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_signal = 0;

/**
 * @brief
 * Executes the minishell program.
 *
 * @details
 * If the command tree has both left and right nodes, it processes the
 * minishell with the command tree. Otherwise, it executes the command
 * in the content of the command tree. After execution, it frees the
 * allocated memory.
 *
 * @param data The minishell data.
 * @return Always returns EXIT_SUCCESS.
 */
static int	minishell(t_minishell *data)
{
	if (data->cmd_tree->left != NULL && data->cmd_tree->right != NULL)
		data->last_status_cmd = proc_minishell(data, data->cmd_tree);
	else
		data->last_status_cmd = exec_command(data->cmd_tree->content, data);
	full_free(data);
	return (EXIT_SUCCESS);
}

/**
 * @brief
 * The main function of the minishell program.
 *
 * @details 
 * This function initializes the minishell data, then enters a loop where it
 * reads lines from the input until the status is STOPPED. For each line, if
 * it's not empty, it adds the line to the history, sets up a signal handler,
 * parses the data, and runs the minishell with the parsed data. After the
 * loop, it deinitializes the data and returns 0.
 *
 * @return 0 on successful execution.
 */
int	main(void)
{
	t_minishell	data;
	char		*line;

	init(&data);
	while (data.status != STOPPED)
	{
		signal(SIGINT, signal_handler_readline);
		line = readline(MINISHELL_ENTRY);
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line != '\0')
		{
			add_history(line);
			signal(SIGINT, signal_handler);
			if (parse_data(line, &data) == EXIT_SUCCESS)
				minishell(&data);
		}
		free(line);
	}
	deinit(&data);
	return (0);
}

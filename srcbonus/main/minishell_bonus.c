/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:18 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:10:33 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_signal = 0;

int	open_pipes(t_minishell *data)
{
	if (pipe(data->pipes) < 0)
		error_init("pipe", 1);
	return (EXIT_SUCCESS);
}

static int	minishell(t_minishell *data)
{
	if (data->cmd_tree->left != NULL && data->cmd_tree->right != NULL)
		data->last_status_cmd = proc_minishell(data, data->cmd_tree);
	else
		data->last_status_cmd = exec_command(data->cmd_tree->content, data);
	full_free(data);
	return (EXIT_SUCCESS);
}

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

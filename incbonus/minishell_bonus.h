/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 10:12:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "title.h"
# include "libft.h"
# include "get_next_line.h"
# include "builtins.h"
# include "structs.h"
# include "parse.h"
# include "utils.h"
# include "strings_utils.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <termcap.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

//*****Signals*****//
void		signal_handler(int signum);
void		controller(t_minishell *data, pid_t *pid);

//*****Command Execution*****//
int			execute_command(t_command *cmd, t_minishell *data);
void		exec_command(t_command *cmd);
void		exec_command_special(t_command *cmd, t_minishell *data);
pid_t		create_process(t_command *cmd, int *pipes,
				int pos, t_minishell *data);

//*****Configurations*****//
void		configurations(void);
void		print_exit(void);
void		deinit(t_minishell *data);
void		init(t_minishell *data);

#endif

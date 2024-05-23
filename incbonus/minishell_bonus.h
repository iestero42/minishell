/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 14:56:44 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "title_bonus.h"
# include "libft.h"
# include "get_next_line.h"
# include "binary_tree.h"
# include "builtins_bonus.h"
# include "structs_bonus.h"
# include "parse_bonus.h"
# include "utils_bonus.h"
# include "strings_utils_bonus.h"

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

//***********SIGNALS***********//
void		signal_handler(int signum);
int			controller(t_minishell *data, pid_t *pid);
void		signal_handler_readline(int signum);

//***********EXECUTION***********//
int			exec_command(t_command *cmd, t_minishell *data);
int			proc_minishell(t_minishell *data, t_tree *tree);

//***********CONFIG***********//
void		hide_eof_symbol(struct termios *term);
void		show_eof_symbol(struct termios *term);
void		configurations(void);
void		deinit(t_minishell *data);
void		init(t_minishell *data);

#endif

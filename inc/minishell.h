/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2023/12/19 10:00:32 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "title.h"
# include "libft.h"
# include "linked_list.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

# define MINISHELL_ENTRY "42-minishell~$ "

# define RUNNING 1
# define STOPPED 2

# define OUTPUT 0
# define INPUT 	1

# define UNQUOTED 	0
# define QUOTED 	1

typedef struct s_command
{
	char	**args;
	char	*name;
	char	*options;
	int		redirection[2];
}	t_command;

typedef struct s_minishell
{
	t_command	*comand_split;
	int			n_comands;
	int			stat;
	int			*pipes;
}	t_minishell;

void		parse_data(const char *command_line, t_minishell *data);

int			ft_strcmp(char *s1, char *s2);

char		**ft_dsubstr(char **str_array, int start_index, int end_index);

void		double_free(char **str);

int			ft_dstrlen(const char **str);

int			split_command(const char *s, char ***command_split);

int			parse_command(char **command_str, t_command *command);

char		**ft_dstrjoin(char **arr1, char **arr2);

void		error_malloc(void);

#endif

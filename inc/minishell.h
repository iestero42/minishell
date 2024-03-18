/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:27:40 by iestero-         ###   ########.fr       */
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

# define UNQUOTED 		0

# define PATH_COMMAND	0

# define ECHO_COMMAND	1
# define CD_COMMAND		2
# define PWD_COMMAND	3
# define EXPORT_COMMAND	4
# define UNSET_COMMAND	5
# define ENV_COMMAND	6
# define EXIT_COMMAND	7

# define NUM_COMMANDS	7

typedef struct s_command
{
	char	**args;
	char	*name;
	int		type;
	int		output_redirect;
	int		last_status;
	int		input_redirect;
}	t_command;

typedef struct s_minishell
{
	t_command	*comand_split;
	int			n_comands;
	int			status;
	int			last_status_cmd;
	int			std_fileno[2];
	char		*cmd_list[NUM_COMMANDS];
	int			*pipes;
	char		**env;
}	t_minishell;

volatile sig_atomic_t	g_signal = 0;

void		parse_data(const char *command_line, t_minishell *data);

int			ft_strcmp(char *s1, char *s2);

char		**ft_dsubstr(char **str_array, int start_index, int end_index);

void		double_free(char **str);

int			ft_dstrlen(const char **str);

char		**split_pipes(const char *s);

char		**split_command(const char *s);

int			parse_command(char *command_str, t_command *command,
				char **cmd_list, int last_status);

char		**ft_dstrjoin(char **arr1, char **arr2);

void		error_malloc(void);

int			built_redirect(char **tokens, t_command *cmd);

int			built_output(char *token, t_command *cmd, char *nex_token);

int			built_input(char *token, t_command *cmd, char *next_token);

int			built_command(char **tokens, t_command *command, char **cmd_list);

int			built_env_variable(char **tokens, int last_status);

char		*ft_copy(const char *token, char *new_token, int start, int len);

int			trim_command(char **tokens);

char		**ft_append(char **arr1, char *str);

int			built_args(t_command *cmd, char **tokens);

void		exec_command(t_command cmd, char **env);

void		exec_command_special(t_command cmd, char **env, t_minishell *data);

void		*ft_realloc(void *ptr, size_t new_size);

void		signal_handler(int signum);

pid_t		create_process(t_command cmd, int *pipes,
				int pos, t_minishell *data);

void		controller(t_minishell *data, pid_t *pid);

int			execute_command(t_command cmd, t_minishell *data);

void		exec_command(t_command cmd, char **env);

int		built_cd(char **args);

int		built_echo(char **args);

int		built_env(void);

int		built_exit(char **args);

int		built_export(char **args);

int		built_pwd(void);

int		built_unset(char **args);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/02 11:11:53 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "title.h"
# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <term.h>
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
# define ERROR_COMMAND	-1

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
	char	*here_doc;
	int		type;
	int		output_redirect;
	int		input_redirect;
}	t_command;

typedef struct s_minishell
{
	t_command		*comand_split;
	struct termios	original_term;
	int				n_comands;
	int				status;
	int				last_status_cmd;
	int				std_fileno[2];
	char			*cmd_list[NUM_COMMANDS];
	int				*pipes;
	char			**env;
}	t_minishell;

int			parse_data(const char *command_line, t_minishell *data);

int			ft_strcmp(char *s1, char *s2);

char		**ft_dsubstr(char **str_array, int start_index, int end_index);

void		double_free(char **str);

int			ft_dstrlen(const char **str);

char		**split_pipes(const char *s);

char		**split_command(const char *s);

int			parse_command(char *command_str, t_command *cmd, t_minishell *data,
				int pos);

char		**ft_dstrjoin(char **arr1, char **arr2);

int			error_init(char *msg);

int			parse_redirect(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_output(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_input(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_command_name(char **tokens, t_command *cmd, char **cmd_list,
				int last_status);

char		*parse_env_variable(char *token, int last_status, int quote);

char		*ft_copy(const char *token, char *new_token, int start, int len);

char		*trim_command(char *token, int last_status);

char		**ft_append(char **arr1, char *str);

int			built_args(t_command *cmd, char **tokens);

void		exec_command_special(t_command *cmd, t_minishell *data);

char		**ft_realloc(char **ptr, char *arg, int count, int expand);

void		signal_handler(int signum);

pid_t		create_process(t_command *cmd, int *pipes,
				int pos, t_minishell *data);

void		controller(t_minishell *data, pid_t *pid);

int			execute_command(t_command *cmd, t_minishell *data);

void		exec_command(t_command *cmd, char ***env);

int			built_cd(char **args);

int			built_echo(char **args);

int			built_env(char **env);

int			built_exit(char **args);

int			built_export(char **args, char ***env);

int			built_pwd(void);

int			built_unset(char **args, char ***env);

void		full_free(t_minishell *data);

void		close_pipes(t_minishell *data);

void		configurations(void);

void		print_exit(void);

char		**ft_dstrdup(const char **str);

int			error_redir(char *tmp, char *org, int pos, t_minishell *data);

#endif

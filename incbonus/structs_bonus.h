/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:20:30 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:49:44 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# define MINISHELL_ENTRY "42-minishell~$ "

# define RUNNING 1
# define STOPPED 2

# define PIPE 		0
# define SEMICOLON 	1
# define AND 		2

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

# define WILDCARD		'\1'
# define INPUT_REDIR	'\3'
# define OUTPUT_REDIR	'\4'
# define ENVP_VAR		'\5'

# include <termios.h>

typedef struct s_command
{
	char	**args;
	char	*name;
	int		type;
	int		output_redirect;
	int		input_redirect;
}	t_command;

typedef struct s_minishell
{
	t_tree			*cmd_tree;
	struct termios	original_term;
	int				n_commands;
	int				status;
	int				last_status_cmd;
	int				std_fileno[2];
	char			*cmd_list[NUM_COMMANDS];
	int				pipes[2];
	int				access_environ;
}	t_minishell;

#endif
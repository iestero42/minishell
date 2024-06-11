/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:19:54 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/11 09:01:53 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

//***********MAIN_PARSE***********//
int			parse_data(char *command_line, t_minishell *data);
int			parse_command(char *command_str, t_minishell *data);

//***********REDIRECTIONS***********//
int			parse_redirect(char **tokens, t_command *cmd,
				char *control, t_minishell *data);
int			parse_input(char **tokens, t_command *cmd,
				char *control, t_minishell *data);
int			parse_output(char **tokens, t_command *cmd, char *control);

//***********EXPANDS***********//
char		*parse_env_variable(char *token, int last_status, int quote);
char		**parse_wildcard(char **token);

//***********COMMAND***********//
int			parse_args(t_command *cmd, char **tokens);
int			parse_command_name(char **tokens, t_command *cmd, char **cmd_list);

#endif
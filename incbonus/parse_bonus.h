/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:19:54 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:14:02 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "structs_bonus.h"

int			parse_data(char *command_line, t_minishell *data);

int			parse_redirect(char **tokens, t_command *cmd,
				char *control, t_minishell *data);

int			parse_output(char **tokens, t_command *cmd, char *control);

int			parse_input(char **tokens, t_command *cmd,
				char *control, t_minishell *data);

int			parse_command_name(char **tokens, t_command *cmd, char **cmd_list);

char		*parse_env_variable(char *token, int last_status, int quote);

char		**parse_wildcard(char **token);

int			parse_args(t_command *cmd, char **tokens);

int			parse_command(char *command_str, t_minishell *data);

#endif
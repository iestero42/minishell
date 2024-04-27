/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:19:54 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 09:31:24 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

int			parse_command(char *command_str, t_command *cmd, t_minishell *data,
				int pos);

int			parse_data(const char *command_line, t_minishell *data);

int			parse_redirect(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_output(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_input(char **tokens, t_command *cmd,
				int pos, t_minishell *data);

int			parse_command_name(char **tokens, t_command *cmd, char **cmd_list);

char		*parse_env_variable(char *token, int last_status, int quote);

char		*parse_wildcard(char *token, int quote);

int			parse_args(t_command *cmd, char **tokens);

#endif
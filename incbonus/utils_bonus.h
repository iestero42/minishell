/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:11:22 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

//*****Misc*****//
char		*readline_own(void);
void		assign_operand(char **tokens, t_tree *tree, int i);
int			check_new_command(int *pos, char **tokens);

//*****Errors*****//
int			error_redir(char *org, char *control);
void		error_export_msg(char *arg);
int			error_unclosed_quotes(char *arg, int len);
int			error_init(char *msg, int error);
int			error_split_operands(int count, int quotes);
int			error_parenthesis(int count_paranthese, char **tokens, int i);
int			error_operands(char **tokens);

//*****Frees*****//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);
int			open_pipes(t_minishell *data);
void		free_cmd(void *cmd);

#endif
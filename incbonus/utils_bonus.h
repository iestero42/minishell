/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 10:20:38 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

//***********MISC***********//
char		*readline_own(char *prompt);
void		assign_operand(char **tokens, t_tree *tree, int i);

//***********ERRORS***********//
int			error_redir(char *org, char *control);
void		error_export_msg(char *arg);
int			error_unclosed_quotes(char *arg, int len);
int			error_init(char *msg, int error);
int			error_split_operands(int count, int quotes);
int			error_parenthesis(int count_paranthese, char **tokens, int i);
int			error_operands(char **tokens);
int			error_command(t_command *cmd, char **tokens);

//***********FREES***********//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);
void		free_cmd(void *cmd);

#endif
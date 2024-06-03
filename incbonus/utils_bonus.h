/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/28 14:20:37 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

//***********MISC***********//
void		assign_operand(char **tokens, t_tree *tree, int i);
char	    **print_estd(char **tokens, int mode, int i);

//***********ERRORS***********//
int			error_redir(char *org, char *control);
void		error_export_msg(char *arg);
int			error_unclosed_quotes(char *arg, int len);
int			error_init(char *msg, int error);
int			error_split_operands(int count, int quotes);
int			error_operands(char **tokens);
int			error_command(t_command *cmd, char **tokens);

//***********CHECK ERRORS***********//
char		**check_err_sintax(char **tokens, t_minishell *data);
void		check_err_heredoc(char *line, int n_line, char *delimiter);

//***********FREES***********//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);
void		free_cmd(void *cmd);

#endif
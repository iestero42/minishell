/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/07 08:22:09 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

//***********MISC***********//
void		assign_operand(char **tokens, t_tree *tree, int i);
char		**print_estd(char **tokens, int mode, int i, t_minishell *data);

//***********ERRORS***********//
int			error_redir(char *org, char *control);
void		error_export_msg(char *arg);
int			error_init(char *msg, int error);
int			error_split_operands(int count, int quotes);
int			error_operands(char **tokens);
int			error_command(t_command *cmd, char **tokens, int type_error);

//***********CHECK ERRORS***********//
char		**check_err_sintax(char **tokens, t_minishell *data, int count);
void		check_err_heredoc(char *line, int n_line, char *delimiter);

//***********FREES***********//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);
void		free_cmd(void *cmd);

#endif
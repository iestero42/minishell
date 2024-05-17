/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:45:42 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

//*****Readlines*****//
char		*readline_own(void);
char		*readline_main(void);

//*****Errors*****//
int			error_redir(char *org, char *control);
void		error_export_msg(char *arg);
int			error_unclosed_quotes(char *arg, int len);
int			error_init(char *msg, int error);
int			error_split_operands(int count, int quotes, const char *s);
int			error_operands(int count_paranthese, char **tokens);

//*****Frees*****//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);
int			open_pipes(t_minishell *data);
void		free_cmd(void *cmd);

#endif
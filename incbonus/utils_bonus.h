/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/06 09:57:51 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

//*****Readlines*****//
char		*readline_own(void);
char		*readline_main(void);

//*****Errors*****//
int			error_redir(char **tmp, char *org, int pos, t_minishell *data);
void		error_export_msg(char *arg);
int			error_unclosed_quotes(char *arg, int len);
int			error_init(char *msg, int error);

//*****Frees*****//
void		full_free(t_minishell *data);
void		close_pipes(t_minishell *data);

#endif
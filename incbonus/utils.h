/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:41 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 09:36:44 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "structs.h"

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:25:32 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/13 11:19:34 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_UTILS_BONUS_H
# define STRINGS_UTILS_BONUS_H

int			ft_strcmp(char *s1, char *s2);

char		**ft_dsubstr(char **str_array, int start_index, int end_index);

void		double_free(char **str);

int			ft_dstrlen(char **str);

char		**split_pipes(char *s);

char		**split_command(const char *s);

char		**ft_dstrjoin(char **arr1, char **arr2);

char		*ft_copy(const char *token, char *new_token, int start, int len);

char		**trim_command(char *token, int last_status);

char		**ft_append(char **arr1, char *str);

char		**ft_dstrdup(char **str);

char		**ft_realloc(char **ptr, char *arg, int count, int expand);

void		convert_wildcard(char *token, char chr, char ctrl, int control);

void		reconvert_tokens(char **tokens);

char		**split_operands(const char *s);

#endif
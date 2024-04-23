/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:25:32 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 09:27:34 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_UTILS_H
# define STRINGS_UTILS_H

int			ft_strcmp(char *s1, char *s2);

char		**ft_dsubstr(char **str_array, int start_index, int end_index);

void		double_free(char **str);

int			ft_dstrlen(char **str);

char		**split_pipes(const char *s);

char		**split_command(const char *s);

char		**ft_dstrjoin(char **arr1, char **arr2);

char		*ft_copy(const char *token, char *new_token, int start, int len);

char		**trim_command(char *token, int last_status);

char		**ft_append(char **arr1, char *str);

char		**ft_dstrdup(char **str);

char		**ft_realloc(char **ptr, char *arg, int count, int expand);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.h                              		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:25:32 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 10:10:51 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_UTILS_H
# define STRINGS_UTILS_H

//***********STRING MATH***********//
int			ft_strcmp(char *s1, char *s2);
int			ft_dstrlen(char **str);

//***********STRING ARRAY MANIPULATION***********//
char		**ft_dsubstr(char **str_array, int start_index, int end_index);
char		**split_command(const char *s);
char		**ft_dstrjoin(char **arr1, char **arr2);
char		**trim_command(char *token, int last_status);
char		**ft_append(char **arr1, char *str);
char		**ft_dstrdup(char **str);

//***********STRING COPY***********//
char		*ft_copy(const char *token, char *new_token, int start, int len);

//***********TOKEN MANIPULATION***********//
void		remove_parenthesis(char **tokens);
void		convert_token(char *tokens);
void		convert_tokens(char **tokens);
void		convert_char(char *token, char chr, char ctrl, int control);

//***********DE/ALLOCATION***********//
void		alloc_environ(t_minishell *data);
void		double_free(char **str);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
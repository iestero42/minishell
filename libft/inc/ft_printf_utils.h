/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:59:44 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/03 12:08:07 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H
# define PERCENT 100
# define CONVERSION 101
# define MINUSFLAG 10
# define ZEROFLAG 5
# define PRECISION 90
# define PLUSFLAG 75
# define HASHFLAG 80
# define SPACEFLAG 70
# define WIDTH 50

# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include "libft.h"
# include "binary_tree.h"

typedef struct ft_printf
{
	char	*org;
	char	*printable;
}	t_print;

char	*check_format(va_list args, char const c);

char	find(char *str, char *to_find);

char	*ft_format_char(char c);

char	*ft_format_str(char *c);

char	*ft_format_int(int n);

char	*ft_format_unsigned(unsigned int n);

char	*ft_format_hex(unsigned int n, int u_l);

char	*ft_format_ptr(unsigned long long p);

char	*fill_zeros(int n, char *str1);

int		ft_formatlen(char *format);

int		ft_calculate_width(char	*str);

char	*ft_spaceflag(t_tree **format, char *print);

char	*ft_precision(t_tree **format, char *print);

char	*ft_plus(t_tree **format, char *print);

char	*ft_hash(t_tree **format, char *print, char *org);

char	*fill_spaces(int n, char *str1, bool R_L);

char	*minus_flag(t_tree **format, char *print);

char	*ft_zeroflag(t_tree **format, char *print);

char	*ft_width(t_tree **format, char *print);

t_print	*check_flags(t_tree **format, va_list args);

char	*numbers(int zeros, char *print, char conversion, t_tree *node);

t_tree	**ft_store_format(char *str);

char	find_zeroflag(char	*str);

void	double_free(char **str);

#endif
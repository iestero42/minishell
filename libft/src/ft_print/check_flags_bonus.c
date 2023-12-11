/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:38:20 by marvin            #+#    #+#             */
/*   Updated: 2022/12/11 10:38:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that saves memory in order to copy a string
 * @param src the string to copy
 * @return char* of the copy or 0 y an error occur
 */
static char	*clone(char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (ft_strdup(""));
	i = ft_strlen(src);
	dest = (char *) malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, src, ft_strlen(src) + 1);
	return (dest);
}

/**
 * Function that check the flags in the format str and change the string to print
 * @param format the tree where are all the flags
 * @param args all the arguments from the va_list
 * @return t_print* with a string with the original and the printable 
 * one with all the flags
 */
t_print	*check_flags(t_tree **format, va_list args)
{
	t_print	*print;
	char	conversion;
	t_tree	*node;

	print = malloc(sizeof(t_print));
	conversion = ft_find_node(CONVERSION, *format)->number;
	print -> printable = check_format(args, conversion);
	print -> org = clone(print -> printable);
	node = ft_find_node(WIDTH, *format);
	if (ft_find_node(PRECISION, *format))
		print -> printable = ft_precision(format, print -> printable);
	if (ft_find_node(HASHFLAG, *format))
		print -> printable = ft_hash(format, print -> printable, print -> org);
	if (ft_find_node(PLUSFLAG, *format))
		print -> printable = ft_plus(format, print -> printable);
	if (ft_find_node(SPACEFLAG, *format))
		print -> printable = ft_spaceflag(format, print -> printable);
	if (ft_find_node(MINUSFLAG, *format))
		print -> printable = minus_flag(format, print -> printable);
	if (ft_find_node(ZEROFLAG, *format))
		print -> printable = ft_zeroflag(format, print -> printable);
	if (!node->left && node->number)
		print -> printable = ft_width(format, print -> printable);
	return (print);
}

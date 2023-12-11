/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:43:09 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 19:43:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function to free the whole tree
 * @param format the tree to free
 */
static void	ft_free_tree(t_tree **format)
{
	ft_clean_tree(format);
	free(format);
}

/**
 * Function that free a whole struct
 * @param print the struct to free
 */
static void	free_printf(t_print *print)
{
	free(print -> printable);
	free(print -> org);
	free(print);
}

/**
 * Function that print the string and any '\0' if its neccesary
 * @param str the string to print 
 * @param format the tree with all the flags and converion to use
 * @param org the original value of the print without the flags modifications
 */
static void	putstr_non(char *str, t_tree **format, const char *org)
{
	int		i;
	t_tree	*node;
	char	conversion;

	i = 0;
	node = ft_find_node(WIDTH, *format);
	conversion = ft_find_node(CONVERSION, *format)->number;
	if (str[i] == '\0' && node->number && ft_find_node(MINUSFLAG, *format))
	{
		ft_putchar_fd('\0', 1);
		i++;
	}
	ft_putstr_fd(&str[i], 1);
	if (!ft_strncmp(org, "", ft_strlen(org)) && conversion == 'c'
		&& !ft_find_node(MINUSFLAG, *format) && node->number)
		ft_putchar_fd('\0', 1);
}

/**
 * Auxiliar function of ft_printf that print the args
 * @param format the tree with all the flags and conversions
 * @param args a list with all the arguments to print
 * @return int of the number of characters printed
 */
static int	ft_printf_aux(t_tree **format, va_list args)
{
	t_print	*print;
	int		count;
	t_tree	*node;
	char	conversion;

	print = check_flags(format, args);
	conversion = ft_find_node(CONVERSION, *format)->number;
	node = ft_find_node(WIDTH, *format);
	if (((!print -> printable || !format) || (conversion == 'c'
				&& !ft_strncmp(print->org, "", ft_strlen(print->org))
				&& ft_find_node(MINUSFLAG, *format))) && !node->number)
	{
		free_printf(print);
		ft_free_tree(format);
		ft_putchar_fd('\0', 1);
		return (1);
	}
	putstr_non(print -> printable, format, (const char *) print -> org);
	if (node->number - (int) ft_strlen((const char *) print -> printable) > 0)
		count = node->number;
	else
		count = (int) ft_strlen((const char *) print -> printable);
	free_printf(print);
	ft_free_tree(format);
	return (count);
}

/**
 * Function that print a number of arguments pass with a specific format
 * @param str the string with the format 
 * @param ... the arguments store in a list
 * @return int of the number of characters printed
 */
int	ft_printf(char const *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += ft_printf_aux(ft_store_format((char *) &str[i]), args);
			i = ft_formatlen((char *) &str[i + 1]) + i;
		}
		else
		{
			count++;
			ft_putchar_fd(str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (count);
}

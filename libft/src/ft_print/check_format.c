/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:46:38 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 13:46:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
* Function that find the correct format and call the appropiate sub_function
* @param args is the argument pass by ft_printf to print
* @param c is the char that tell what kind of type is
* @return the string with the conversion done
*/
char	*check_format(va_list args, char const c)
{
	char	*str;

	str = 0;
	if (c == 'c')
		str = ft_format_char(va_arg(args, int));
	else if (c == 'p')
		str = ft_format_ptr(va_arg(args, unsigned long long));
	else if (c == 's')
		str = ft_format_str(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		str = ft_format_int(va_arg(args, int));
	else if (c == 'u')
		str = ft_format_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		str = ft_format_hex(va_arg(args, unsigned int), 87);
	else if (c == 'X')
		str = ft_format_hex(va_arg(args, unsigned int), 55);
	else if (c == '%')
		str = ft_strdup("%");
	return (str);
}

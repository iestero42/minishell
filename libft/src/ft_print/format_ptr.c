/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:55:50 by marvin            #+#    #+#             */
/*   Updated: 2022/12/11 13:55:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that calculate the number of digits 
 * @param n is the number from it calculate the number of digits
 * @return the number of digits
*/
static int	ft_size_ptr(unsigned long long n)
{
	int	i;

	i = 0;
	while (n / 16 > 0)
	{
		n = n / 16;
		i++;
	}
	return (i + 1);
}

/**
 * Auxiliar function that in a recursive way stores the hexadecimal in a string
 * @param n the number to convert
 * @param i indicate the position inside the string
 * @param str is where the number is store
 * @return the size of the string 
*/
static int	ft_hex_ptr_aux(unsigned long long n, int i, char *str)
{
	unsigned int	tmp;

	if (n > 0)
	{
		i = ft_hex_ptr_aux(n / 16, i, str);
		tmp = n % 16;
		if (tmp < 10)
			str[i] = 48 + tmp;
		else
			str[i] = 87 + tmp;
		i++;
	}
	return (i);
}

/**
 * Auxiliar function that save memory to store a number inside a string
 * @param n the number to store
 * @return the string with the number inside 
*/
static char	*ft_hex_ptr(unsigned long long n)
{
	char	*str;
	int		i;

	str = 0;
	i = ft_size_ptr(n);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_hex_ptr_aux(n, 0, str);
	str[i] = '\0';
	return (str);
}

/**
 * Function that save memory to store a direction in a string
 * using sub_functions
 * @param n the direction to store
 * @return the string with the direction inside 
*/
char	*ft_format_ptr(unsigned long long p)
{
	char		*aux;
	char		*ptr;
	uintptr_t	addr;

	aux = 0;
	ptr = 0;
	if (!p)
		return (ft_strdup("0x0"));
	addr = (uintptr_t) p;
	aux = ft_hex_ptr(addr);
	ptr = ft_strjoin("0x", aux);
	free(aux);
	return (ptr);
}

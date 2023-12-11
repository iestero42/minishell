/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:09:07 by marvin            #+#    #+#             */
/*   Updated: 2022/12/05 11:09:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that calculate the number of digits of a hexadecimal number
 * @param n is the number to convert to hexadecimal
 * @return the number of digits 
*/
static int	ft_size_hex(unsigned int n)
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
 * Auxiliar function that in a recursive way stores the number in a string
 * @param n the number to convert to hexadecimal
 * @param u_l indicate if the letters are in upper or lowercase
 * @param i indicate the position inside the string
 * @param str is where the number is store
 * @return the size of the string 
*/
static int	ft_format_hex_aux(unsigned int n, int u_l, int i, char *str)
{
	unsigned int	tmp;

	if (n > 0)
	{
		i = ft_format_hex_aux(n / 16, u_l, i, str);
		tmp = n % 16;
		if (tmp < 10)
			str[i] = 48 + tmp;
		else
			str[i] = u_l + tmp;
		i++;
	}
	return (i);
}

/**
 * Function to save memory to convert a number to hexadecimal and store 
 * it in a string
 * @param n the number to convert to hexadecimal
 * @param u_l indicate if the letters are in upper or lowercase
 * @return the string with the hexadecimal inside
*/
char	*ft_format_hex(unsigned int n, int u_l)
{
	char	*str;
	int		i;

	if (!n)
		return (ft_strdup("0"));
	str = 0;
	i = ft_size_hex(n);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_format_hex_aux(n, u_l, 0, str);
	str[i] = '\0';
	return (str);
}

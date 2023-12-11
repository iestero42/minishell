/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:26:17 by marvin            #+#    #+#             */
/*   Updated: 2022/12/05 10:26:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that save memory to store an int inside a string
 * @param n the number to store
 * @return the string
*/
char	*ft_format_int(int n)
{
	return (ft_itoa(n));
}

/**
 * Auxiliar function that in a recursive way stores the number in a string
 * @param n the number to store
 * @param ctrl use to control if we want or not to store the number
 * @param i indicate the position inside the string
 * @param str is where the number is store
 * @return the size of the string 
*/
static int	ft_rec_istr(unsigned int n, char *str, int i, int ctrl)
{
	unsigned int	temp;

	temp = 0;
	if (n > 0)
	{
		i = ft_rec_istr(n / 10, str, i, ctrl);
		temp = n % 10;
		if (ctrl)
			str[i] = temp + 48;
		i++;
	}
	return (i);
}

/**
 * Auxiliar function that save memory to store a number inside a string
 * @param n the number to store
 * @return the string with the number inside 
*/
static char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;

	str = 0;
	i = ft_rec_istr(n, str, 0, 0);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_rec_istr(n, str, 0, 1);
	str[i] = '\0';
	return (str);
}

/**
 * Function that save memory to store a number inside a string
 * using sub_function
 * @param n the number to store
 * @return the string with the number inside 
*/
char	*ft_format_unsigned(unsigned int n)
{
	char	*num;

	if (n == 0)
		num = ft_strdup("0");
	else
		num = ft_uitoa(n);
	return (num);
}

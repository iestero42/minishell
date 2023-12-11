/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:58:55 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 19:58:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that find in a string the first ocurrence of any char 
 * from other string
 * @param str the string where the search is made
 * @param to_find the string with all the chars to find
 * @return the char if its found or 0 on any other case
*/
char	find(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0')
		{
			if (str[i] == to_find[j])
				return (str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Function that calculate the length of the format string
 * @param format the string where the length calculation is made
 * @return int product of the length calculation
*/
int	ft_formatlen(char *format)
{
	int	i;

	i = 0;
	while (format[i] != '\0' && format[i] != find(format, "cspdiuxX%"))
		i++;
	return (i + 1);
}

/**
 * Function that fill with zeros a string until length n is reach
 * @param n the number of zeros 
 * @param str1 the string where all the zeros goes
 * @return char* product of concatenate the zeros with the string
*/
char	*fill_zeros(int n, char *str1)
{
	char	*str;
	char	*aux;
	int		i;

	i = 0;
	str = (char *) malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	ft_bzero(str, n + 1);
	while (i < n)
		str[i++] = '0';
	aux = ft_strjoin(str, str1);
	free(str);
	return (aux);
}

/**
 * Function that fill with spaces a string until length n is reach
 * @param n the number of spaces 
 * @param str1 the string where all the spaces goes
 * @return char* product of concatenate the spaces with the string
*/
char	*fill_spaces(int n, char *str1, bool R_L)
{
	char	*str;
	char	*aux;
	int		i;

	i = 0;
	str = (char *) malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	ft_bzero(str, n + 1);
	while (i < n)
		str[i++] = ' ';
	if (R_L)
		aux = ft_strjoin(str1, str);
	else
		aux = ft_strjoin(str, str1);
	free(str);
	return (aux);
}

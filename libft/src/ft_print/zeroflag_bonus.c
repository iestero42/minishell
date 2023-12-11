/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeroflag_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:14:34 by marvin            #+#    #+#             */
/*   Updated: 2022/12/11 10:14:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Auxiliar function that fill with zeros the print without the "0x" and 
 * then its added again
 * @param print the string to fill with zeros
 * @param n the number of zeros
 * @return char* with all the modification done if needed
*/
static char	*zeroflag_aux(char *print, int n)
{
	char	*tmp;

	tmp = ft_substr(print, 3, ft_strlen(print) - 2);
	free(print);
	print = fill_zeros(n, tmp);
	free(tmp);
	tmp = ft_strdup(print);
	free(print);
	print = ft_strjoin("0x", tmp);
	return (print);
}

/**
 * Fucntion that implements the zeroflag by adding "0" to the string to print
 * @param format the tree use to calculate the width to use 
 * @param print the string that will be filled with "0"
 * @return char* with all the modification done
*/
char	*ft_zeroflag(t_tree **format, char *print)
{
	char	*tmp;
	char	cnv;
	int		n;

	n = ft_find_node(ZEROFLAG, *format)->number;
	cnv = ft_find_node(CONVERSION, *format)->number;
	if (!print)
		return (print);
	n -= (int) ft_strlen(print);
	if (cnv != 's' && cnv != 'c' && !ft_find_node(PRECISION, *format) && n > 0)
	{
		if (cnv == 'd' || cnv == 'i' || cnv == 'u' || cnv == 'x' || cnv == 'X')
		{
			tmp = numbers(n, print, cnv, ft_find_node(PERCENT, *format));
			free(print);
			print = tmp;
		}
		else if (cnv == 'p')
			print = zeroflag_aux(print, n);
	}
	else if ((cnv == 's' || cnv == 'c'
			|| ft_find_node(PRECISION, *format)) && n > 0)
		print = ft_width(format, print);
	return (print);
}

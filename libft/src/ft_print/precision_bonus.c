/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:19:57 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 20:19:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that concatenate two string
 * @param print the string where the concatenation goes
 * @param s the first string to concatenate
 * @param tmp the second string to concatenate
 * @return char* with the concatenation done
*/
static char	*concanate(char *print, char *tmp, char *s)
{
	if (print[1] == 'X')
		s = "0X";
	print = ft_strjoin(s, tmp);
	free(tmp);
	return (print);
}

/**
 * Function that find diferents modifications done by other flags in order 
 * to correctly add the zeros
 * @param print the string that will be filled and where all this 
 * odification can be seen
 * @param zeros the number of zeros
 * @return char* with all the modification done
*/
static char	*find_flag(char *print, int zeros)
{
	char	*tmp;
	int		n;

	n = 0;
	if (print[0] == ' ' || print[0] == '+')
	{
		++print;
		n = 1;
	}
	else if (print[0] == '0' && (print[1] == 'x' || print[1] == 'X'))
	{
		print = print + 2;
		n = 2;
	}
	tmp = fill_zeros(zeros, print);
	print = print - n;
	if (print[0] == ' ')
		print = concanate(print, tmp, " ");
	else if (print[0] == '+')
		print = concanate(print, tmp, "+");
	else if (print[0] == '0' && (print[1] == 'x' || print[1] == 'X'))
		print = concanate(print, tmp, "0x");
	else
		print = tmp;
	return (print);
}

/**
 * Function that finds if there is any sign before the number string and 
 * fill in a correct way the string with zeros
 * @param zeros the number of zeros
 * @param conversion the type of conversion
 * @param print the string where the signs are and where the that will be filled
 * @param node the node of the main tree
 * @return char* with the zeros added in a correct way
*/
char	*numbers(int zeros, char *print, char conversion, t_tree *node)
{
	int		n;
	char	*tmp;

	n = ft_atoi(print);
	if (node->key == PRECISION && !ft_strncmp(print, "0", ft_strlen(print))
		&& !node->number)
		return (ft_strdup(""));
	if (n < 0 && conversion != 'u' && conversion != 'x' && conversion != 'X')
	{
		tmp = fill_zeros(zeros, ++print);
		print = ft_strjoin("-", tmp);
		free(tmp);
	}
	else
		print = find_flag(print, zeros);
	return (print);
}

/**
 * Auxiliar function that parcially implements the precision flag in the way 
 * that the conversion require adding zeros before a string 
 * @param print the string to fill with zeros
 * @param conversion the type of conversion
 * @param n the number of zeros 
 * @param node the node of the main tree
 * @return char* with the zeros added if it was needed
*/
static char	*precision_aux(char *print, char conversion, int n, t_tree *node)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(print);
	free(print);
	if (conversion == 'd' || conversion == 'i' || conversion == 'u'
		|| conversion == 'x' || conversion == 'X')
		print = numbers(n, tmp, conversion, node);
	else if (conversion == 's')
		print = ft_substr(tmp, 0, n);
	else if (conversion == 'p')
	{
		tmp2 = ft_substr(tmp, 3, ft_strlen(tmp) - 2);
		free(tmp);
		print = fill_zeros(n, tmp2);
		free(tmp2);
		tmp = ft_strdup(print);
		free(print);
		print = ft_strjoin("0x", tmp);
	}
	free(tmp);
	return (print);
}

/**
 * Auxiliar function that fully implements the precision flag in the way 
 * that the conversion require adding zeros before a string 
 * @param print the string to fill with zeros
 * @param format the tree where the conversion type and the number of zeros is
 * @return char* with the zeros added if it was needed
*/
char	*ft_precision(t_tree **format, char *print)
{
	int		n;
	t_tree	*node;
	char	conversion;
	int		tmp;

	node = ft_find_node(PRECISION, *format);
	n = node->number;
	conversion = ft_find_node(CONVERSION, *format)->number;
	if (conversion == 'd' || conversion == 'i' || conversion == 'u'
		|| conversion == 'x' || conversion == 'X' || conversion == 's'
		|| conversion == 'p')
	{
		if (ft_atoi(print) < 0 && (conversion == 'd' || conversion == 'i'))
			tmp = n - (int) ft_strlen((const char *)(print + 1));
		else
			tmp = n - (int) ft_strlen((const char *) print);
		if (tmp < 0 && conversion != 's')
			n = 0;
		else if (conversion != 's')
			n = tmp;
		print = precision_aux(print, conversion, n, node);
	}
	return (print);
}

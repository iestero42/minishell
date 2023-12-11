/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:52:49 by marvin            #+#    #+#             */
/*   Updated: 2022/12/10 19:52:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdio.h>

/**
 * Function that return a string that ends with double '\0'
 * @param n the number of spaces to put in the string
 * @return char* with the '\0' end and the spaces or null if error occur
 */
static char	*empty_str2(int n)
{
	char	*tmp;
	char	*tmp1;
	int		j;

	tmp = fill_spaces(n - 1, "", false);
	tmp1 = (char *) malloc(sizeof(char) * ((int) ft_strlen(tmp) + 2));
	if (!tmp1)
		return (0);
	j = 0;
	while (tmp[j] != '\0')
	{
		tmp1[j] = tmp[j];
		j++;
	}
	tmp1[j++] = '\0';
	tmp1[j] = '\0';
	free(tmp);
	return (tmp1);
}

/**
 * Function that free a double pointer
 * @param str the double pointer to free
*/
void	double_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

/**
 * Function that check if there is width in the format string
 * @param str the string where look for the width
 * @return int 1 if found or 0 if not
*/
static int	check_width(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.' && str[i] != '\0')
	{
		if (str[i] > '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

/**
 * Function that calculate the width from the format string
 * @param str the string where look for the width
 * @return int that represents the width 
*/
int	ft_calculate_width(char	*str)
{
	char	**num;
	int		n;
	int		i;

	i = 0;
	if (find(str, ".") && !check_width(str))
		return (0);
	num = ft_split(str, '.');
	if (!num)
		return (0);
	while ((num[0][i] <= '0' || num[0][i] > '9') && num[0][i] != '\0')
		i++;
	if (!num[0][i])
		n = 0;
	else
		n = ft_atoi(&num[0][i]);
	double_free(num);
	return (n);
}

/**
 * Function that implements the width adding ' ' before the string to print
 * @param format the tree where the width is extrated
 * @param print the string to print
 * @return char* product of modificate print adding the spaces when needed
*/
char	*ft_width(t_tree **format, char *print)
{
	int		n;
	char	*tmp;

	n = ft_find_node(WIDTH, *format)->number;
	if (!n)
		return (print);
	if (!print)
		return (empty_str2(n));
	n -= (int) ft_strlen(print);
	if (n > 0)
	{
		tmp = fill_spaces(n, print, false);
		free(print);
		print = tmp;
	}
	return (print);
}

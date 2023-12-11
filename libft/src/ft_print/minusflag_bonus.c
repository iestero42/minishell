/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minusflag_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:57:11 by marvin            #+#    #+#             */
/*   Updated: 2022/12/08 19:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that return a string that starts with '\0'
 * @param n the number of spaces to put in the string
 * @return char* with the '\0' start and the spaces or null if error occur
 */
static char	*empty_str(int n)
{
	char	*tmp;
	char	*tmp1;
	int		i;
	int		j;

	tmp = fill_spaces(n - 1, "", true);
	tmp1 = (char *) malloc(sizeof(char) * ((int) ft_strlen(tmp) + 2));
	if (!tmp1)
		return (0);
	i = 0;
	tmp1[i++] = '\0';
	j = 0;
	while (tmp[j] != '\0')
		tmp1[i++] = tmp[j++];
	tmp1[i] = '\0';
	free(tmp);
	return (tmp1);
}

/**
 * Function that implements the minusflag adding spaces after the argument
 * @param tree the tree with the '-' on it
 * @param print the string wher all the spaces go
 * @return char* with the minusflag modification done if its done
 */
char	*minus_flag(t_tree **format, char *print)
{
	int		n;
	char	*tmp;

	n = ft_find_node(MINUSFLAG, *format)->number;
	if (!print)
		return (empty_str(n));
	n -= (int) ft_strlen(print);
	if (n > 0)
	{
		tmp = fill_spaces(n, print, true);
		free(print);
		print = tmp;
	}
	return (print);
}

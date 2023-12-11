/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:46:29 by marvin            #+#    #+#             */
/*   Updated: 2022/12/09 15:46:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that implements the plusflag adding '+' if the int have no sign
 * @param tree the tree where the '+' should be
 * @param print the string where the '+' go 
 * @return char* with the plusflag modification done
 */
char	*ft_plus(t_tree **format, char *print)
{
	char	*s;
	char	conversion;

	s = 0;
	conversion = ft_find_node(CONVERSION, *format)->number;
	if (conversion == 'd' || conversion == 'i' || conversion == 'p')
	{
		if (conversion == 'p')
		{
			s = ft_strjoin("+", print);
			free(print);
			print = s;
		}
		if ((conversion == 'd' || conversion == 'i') && *print != '-')
		{
			s = ft_strjoin("+", print);
			free(print);
			print = s;
		}
	}
	return (print);
}

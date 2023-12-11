/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaceflag_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:03:48 by marvin            #+#    #+#             */
/*   Updated: 2022/12/10 19:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that implements the spaceflag adding ' ' to the string 
 * @param str the where look for the ' ' in order to make the modification
 * @param format the tree where the ' ' will be added 
 * @return char* with the modification done
*/
char	*ft_spaceflag(t_tree **format, char *print)
{
	char	*tmp;
	char	conversion;

	tmp = 0;
	conversion = ft_find_node(CONVERSION, *format)->number;
	if (conversion == 'd' || conversion == 'i' || conversion == 'p')
	{
		if (*print != '-' && *print != '+')
		{
			tmp = ft_strjoin(" ", print);
			free(print);
			print = tmp;
		}
	}
	return (print);
}

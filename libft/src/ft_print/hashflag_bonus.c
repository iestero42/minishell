/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:01:03 by marvin            #+#    #+#             */
/*   Updated: 2022/12/09 10:01:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that implements the hashflag adding "0x" or "0X" to the print string
 * @param format the tree where the '#' should be 
 * @param print the string where is added the preffix "0x" or "0X"
 * @param org the original string without flag modifications
 * @return char* with the hashflag modification done
 */
char	*ft_hash(t_tree **format, char *print, char *org)
{
	char	*s;
	char	conversion;

	s = 0;
	conversion = ft_find_node(CONVERSION, *format)->number;
	if ((conversion == 'x' || conversion == 'X')
		&& ft_strncmp(org, "0", ft_strlen(print)))
	{
		if (conversion == 'x')
			s = ft_strjoin("0x", print);
		else
			s = ft_strjoin("0X", print);
		free(print);
		print = s;
	}
	return (print);
}

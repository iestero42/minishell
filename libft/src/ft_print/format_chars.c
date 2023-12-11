/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:59:08 by marvin            #+#    #+#             */
/*   Updated: 2022/12/05 09:59:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that save memory to store a char into a string
 * @param c is the char to store
 * @return the string 
*/
char	*ft_format_char(char c)
{
	char	*str;

	if (!c)
		return (0);
	str = (char *) malloc(2 * sizeof(char));
	if (!str)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/**
 * Function that save memory for a string
 * @param c is the char to store
 * @return the string 
*/
char	*ft_format_str(char *c)
{
	char	*str;

	if (c == NULL)
		return (ft_strdup("(null)"));
	str = ft_strdup(c);
	return (str);
}

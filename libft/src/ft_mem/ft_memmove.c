/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:57:34 by iestero-          #+#    #+#             */
/*   Updated: 2023/03/15 15:06:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	int	i;

	if (!str1 && !str2)
		return (str1);
	if (str1 > str2)
	{
		i = (int) n - 1;
		while (i >= 0)
		{
			*(char *)(str1 + i) = *(char *)(str2 + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int) n)
		{
			*(char *)(str1 + i) = *(char *)(str2 + i);
			i++;
		}
	}
	return (str1);
}

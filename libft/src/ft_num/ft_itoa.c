/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:26:52 by iestero-          #+#    #+#             */
/*   Updated: 2023/03/15 15:06:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_rec_istr(int n, char *str, int i, int ctrl)
{
	int			temp;

	temp = 0;
	if (n < 0)
	{
		if (ctrl)
			str[i] = '-';
		i++;
		n = n * -1;
	}
	if (n > 0)
	{
		i = ft_rec_istr(n / 10, str, i, ctrl);
		temp = n % 10;
		if (ctrl)
			str[i] = temp + 48;
		i++;
	}
	return (i);
}

static int	ft_istr(int n, char *str, int i, int ctrl)
{
	if (n == 0)
	{
		if (ctrl)
			str[i] = '0';
		i++;
	}
	if (n == -2147483648)
	{
		if (ctrl)
		{
			str[0] = '-';
			str[1] = '2';
		}
		i = 2;
		n = 147483648;
	}
	if (n != 0 && n != -2147483648)
		i = ft_rec_istr(n, str, i, ctrl);
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = 0;
	i = ft_istr(n, str, 0, 0);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_istr(n, str, 0, 1);
	str[i] = '\0';
	return (str);
}

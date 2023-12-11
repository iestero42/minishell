/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:57:03 by iestero-          #+#    #+#             */
/*   Updated: 2023/03/15 15:06:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_cut_end(char const *s1, char const *set)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(s1);
	j = 0;
	while (j < len)
	{
		if (ft_strchr(set, s1[len - j - 1]) == 0)
			break ;
		j++;
	}
	return (j);
}

static int	ft_cut_start(char const *s1, char const *set)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(s1);
	j = 0;
	while (j < len)
	{
		if (ft_strchr(set, s1[j]) == 0)
			break ;
		j++;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;
	char	*str_final;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = ft_cut_start(s1, set);
	end = ft_cut_end(s1, set);
	len = ft_strlen(s1) - start - end;
	if (len <= 0)
		return (ft_strdup(""));
	str_final = ft_substr(s1, start, len);
	return (str_final);
}

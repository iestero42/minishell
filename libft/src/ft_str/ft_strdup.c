/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:26:23 by iestero-          #+#    #+#             */
/*   Updated: 2023/03/15 15:06:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	dup = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = (char) s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

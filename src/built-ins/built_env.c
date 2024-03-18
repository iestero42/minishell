/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:58:52 by iestero-          #+#    #+#             */
/*   Updated: 2024/03/18 11:27:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] < NULL)
	{
		ft_putstr_fd(environ[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

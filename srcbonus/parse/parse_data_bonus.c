/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:48:47 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/22 16:01:21 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

extern volatile sig_atomic_t	g_signal;

int	parse_data(char *command_line, t_minishell *data)
{
	char	*tmp;
	int		result;

	g_signal = 0;
	tmp = ft_strtrim(command_line, " ");
	if (!tmp)
		error_init("ft_strtrim", 1);
	if (*tmp == '\0')
	{
		free(tmp);
		return (EXIT_FAILURE);
	}
	result = parse_command(tmp, data);
	free(tmp);
	return (result);
}

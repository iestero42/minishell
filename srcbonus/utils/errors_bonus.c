/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:53:30 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/15 12:40:35 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	error_init(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	error_redir(char *tmp, char *org, int pos, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	if ((tmp == NULL || *tmp == '\0') && pos == data->n_comands - 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (((tmp == NULL || *tmp == '\0') && pos < data->n_comands - 1))
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	if (tmp)
	{
		if (ft_strcmp(tmp, org) && *tmp == '\0')
		{
			ft_putstr_fd(org, 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
		}
		else if (*tmp == '<' || *tmp == '>')
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("\n", 2);
		}
		free(tmp);
	}
	return (EXIT_FAILURE);
}

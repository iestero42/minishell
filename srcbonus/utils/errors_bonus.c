/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:53:30 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/09 08:31:14 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	error_init(char *msg, int error)
{
	perror(msg);
	exit(error);
}

int	error_redir(char **tmp, char *org, int pos, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	if ((tmp == NULL || **tmp == '\0') && pos == data->n_comands - 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (((tmp == NULL || **tmp == '\0') && pos < data->n_comands - 1))
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	if (tmp)
	{
		if (ft_strcmp(tmp[0], org) && **tmp == '\0')
		{
			ft_putstr_fd(org, 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
		}
		else if (tmp[0][0] == '<' || tmp[0][0] == '>')
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putstr_fd(tmp[0], 2);
			ft_putstr_fd("\n", 2);
		}
		double_free(tmp);
	}
	return (EXIT_FAILURE);
}

void	error_export_msg(char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
}

int	error_unclosed_quotes(char *arg, int len)
{
	int		i;
	char	quotes;

	i = -1;
	quotes = 0;
	while (++i < len)
	{
		if ((arg[i] == '\'' || arg[i] == '"') && !quotes)
			quotes = arg[i];
		else if (arg[i] == quotes && quotes)
			quotes = 0;
	}
	return (quotes);
}

int	error_split_operands(int count, int quotes, const char *s)
{
	if (quotes)
	{
		ft_putstr_fd("minishell: syntax error near 'newline'\n", 2);
		return (-2);
	}
	else if (count == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putchar_fd(s[0], 2);
		ft_putchar_fd('\n', 2);
		return (-2);
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:53:30 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:36:58 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file errors_bonus.c
 * @brief Contains functions for handling errors.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Handles initialization errors.
 *
 * @details
 * Prints an error message and exits the program with a specified error code.
 *
 * @param msg The error message.
 * @param error The error code.
 * @return Does not return.
 */
int	error_init(char *msg, int error)
{
	perror(msg);
	exit(error);
}

/**
 * @brief 
 * Handles redirection errors.
 *
 * @details
 * Prints an error message depending on the type of redirection error.
 *
 * @param org The original command.
 * @param control The control character.
 * @return Always returns EXIT_FAILURE.
 */
int	error_redir(char *org, char *control)
{
	ft_putstr_fd("minishell: ", 2);
	if ((org == NULL || *org == '\0') && control == NULL)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (((org == NULL || *org == '\0') && control != NULL))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(control, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (org)
	{
		if (*org == ENVP_VAR)
		{
			ft_putstr_fd(org, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
		}
		else if (*org == '<' || *org == '>')
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putstr_fd(org, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (EXIT_FAILURE);
}

/**
 * @brief 
 * Prints an error message for invalid export arguments.
 *
 * @param arg The invalid argument.
 */
void	error_export_msg(char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
}

/**
 * @brief 
 * Checks for unclosed quotes in a string.
 *
 * @details
 * Iterates over the characters in a string. If it finds an unclosed quote, 
 * it returns the quote character.
 *
 * @param arg The string to check.
 * @param len The length of the string.
 * @return The unclosed quote character, or 0 if all quotes are closed.
 */
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

/**
 * @brief 
 * Handles errors in split operands.
 *
 * @details
 * Prints an error message if there are unclosed quotes or unexpected '&' tokens.
 *
 * @param count The number of operands.
 * @param quotes The quote status.
 * @return The number of operands, or -2 if there is an error.
 */
int	error_split_operands(int count, int quotes)
{
	if (quotes)
	{
		ft_putstr_fd("minishell: syntax error near 'newline'\n", 2);
		return (-2);
	}
	else if (count == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '&'\n", 2);
		return (-2);
	}
	return (count);
}

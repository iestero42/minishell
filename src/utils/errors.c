/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:53:30 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/17 08:31:34 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file errors_bonus.c
 * @brief Contains functions for handling errors.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell.h"

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

static void	print_error_redir(char *org)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	if (*org == INPUT_REDIR)
		ft_putstr_fd("`<'\n", STDERR_FILENO);
	else
		ft_putstr_fd("`>'\n", STDERR_FILENO);
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (org == NULL && control == NULL)
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	else if (org == NULL && control != NULL)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(control, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	if (org)
	{
		if (*org == ENVP_VAR)
		{
			ft_putstr_fd(org, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		}
		else if (*org == INPUT_REDIR || *org == OUTPUT_REDIR)
			print_error_redir(org);
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
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

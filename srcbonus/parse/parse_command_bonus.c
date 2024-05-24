/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:50:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/24 08:39:00 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_command_bonus.c
 * @brief Contains the functions for parsing commands.
 * @author yunlovex <yunlovex@student.42.fr>
 * @date 2024/05/23
 */

#include "minishell_bonus.h"

/**
 * @brief 
 * Handles an error in command parsing.
 *
 * @details
 * Sets the command type to ERROR_COMMAND, clears the name and args,
 * and frees the tokens.
 *
 * @param cmd The command structure to modify.
 * @param tokens The tokens to free.
 * @return Always returns EXIT_SUCCESS.
 */
static int	error_command(t_command *cmd, char **tokens)
{
	cmd->type = ERROR_COMMAND;
	cmd->name = NULL;
	cmd->args = NULL;
	double_free(tokens);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Trims the arguments from the tokens.
 *
 * @details
 * Iterates over the tokens, trims each one, and appends
 * it to the new_token array.
 *
 * @param tokens The tokens to trim.
 * @param last_status The last status of the command.
 * @param data The minishell data.
 * @return The new_token array.
 */
static char	**trim_args(char **tokens, int last_status, t_minishell *data)
{
	int		i;
	char	**tmp;
	char	**new_token;

	i = 0;
	new_token = 0;
	alloc_environ(data);
	while (tokens[i] != NULL)
	{
		if (*tokens[i] != '\0')
		{
			tmp = trim_command(tokens[i], last_status);
			new_token = ft_dstrjoin(new_token, tmp);
			free(tmp);
			if (!new_token)
				return (NULL);
		}
		i++;
	}
	if (!new_token)
		new_token = ft_dstrdup(tokens);
	return (new_token);
}

/**
 * @brief 
 * Parses a subcommand from the tokens.
 *
 * @details
 * Trims the arguments, parses the redirection, command name, and arguments,
 * and handles any errors that occur.
 *
 * @param tokens The tokens to parse.
 * @param cmd The command structure to fill.
 * @param data The minishell data.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	parse_subcmd(char **tokens, t_command *cmd, t_minishell *data,
		char *control)
{
	char	**new_tokens;

	new_tokens = trim_args(tokens, data->last_status_cmd, data);
	if (!new_tokens)
		error_init("malloc", 1);
	if (parse_redirect(new_tokens, cmd, control, data) == EXIT_FAILURE)
		return (error_command(cmd, new_tokens));
	if (data->status == STOPPED)
	{
		double_free(new_tokens);
		data->status = RUNNING;
		return (EXIT_FAILURE);
	}
	if (parse_command_name(new_tokens, cmd, data->cmd_list) == EXIT_FAILURE)
		return (error_command(cmd, new_tokens));
	if (parse_args(cmd, new_tokens) == EXIT_FAILURE)
		return (error_command(cmd, new_tokens));
	double_free(new_tokens);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Recursively parses a command from the tokens.
 *
 * @details
 * Removes parentheses, checks for a new command, and recursively parses
 * the left and right subcommands.
 *
 * @param tokens The tokens to parse.
 * @param data The minishell data.
 * @param tree The command tree to fill.
 * @param control The control character.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int	parse_command_rec(char **tokens, t_minishell *data, t_tree *tree,
				char *control)
{
	int		i;
	char	**tmp;

	i = 0;
	remove_parenthesis(tokens);
	if (check_new_command(&i, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tokens[i] == NULL)
	{
		tree->content = (t_command *) malloc(sizeof(t_command));
		return (parse_subcmd(tokens, tree->content, data, control));
	}
	tree->left = ft_new_node(0, NULL, 0);
	tmp = ft_dsubstr(tokens, 0, i - 1);
	if (!tmp)
		error_init("malloc", 1);
	if (parse_command_rec(tmp, data, tree->left, tokens[i]) == 1)
		return (EXIT_FAILURE);
	double_free(tmp);
	tree->right = ft_new_node(0, NULL, 0);
	if (parse_command_rec(&tokens[i + 1], data, tree->right, tokens[i]) == 1)
		return (EXIT_FAILURE);
	assign_operand(tokens, tree, i);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * Parses a command from a string.
 *
 * @details
 * Splits the command string into tokens, creates a new command tree,
 * and recursively parses the command.
 *
 * @param command_str The command string to parse.
 * @param data The minishell data.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	parse_command(char *command_str, t_minishell *data)
{
	char		**tokens;
	int			result;

	tokens = split_command(command_str);
	if (!tokens)
		return (EXIT_FAILURE);
	data->cmd_tree = ft_new_node(0, NULL, 0);
	if (!data->cmd_tree)
		error_init("malloc", 1);
	result = parse_command_rec(tokens, data, data->cmd_tree, NULL);
	double_free(tokens);
	return (result);
}

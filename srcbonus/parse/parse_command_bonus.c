/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:50:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/23 09:11:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	error_command(t_command *cmd, char **tokens)
{
	cmd->type = ERROR_COMMAND;
	cmd->name = NULL;
	cmd->args = NULL;
	double_free(tokens);
	return (EXIT_SUCCESS);
}

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

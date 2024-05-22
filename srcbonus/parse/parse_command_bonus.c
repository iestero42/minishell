/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:50:36 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/22 16:04:14 by yunlovex         ###   ########.fr       */
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
	if (new_token)
		double_free(tokens);
	else
		return (tokens);
	return (new_token);
}

static int	parse_subcmd(char *command_str, t_command *cmd, t_minishell *data,
		char *control)
{
	char	**tokens;
	char	*cmd_trimmed;

	cmd_trimmed = ft_strtrim(command_str, " ");
	if (!cmd_trimmed)
		error_init("ft_strtrim", 1);
	tokens = split_command(cmd_trimmed);
	free(cmd_trimmed);
	tokens = trim_args(tokens, data->last_status_cmd, data);
	if (!tokens)
		error_init("malloc", 1);
	if (parse_redirect(tokens, cmd, control, data) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	if (data->status == STOPPED)
	{
		double_free(tokens);
		data->status = RUNNING;
		return (EXIT_FAILURE);
	}
	if (parse_command_name(tokens, cmd, data->cmd_list) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	if (parse_args(cmd, tokens) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	double_free(tokens);
	return (EXIT_SUCCESS);
}

static int	parse_command_rec(char **tokens, t_minishell *data, t_tree *tree,
				char *control)
{
	int	count_parentheses;
	int	i;

	count_parentheses = 0;
	i = -1;
	remove_parenthesis(tokens);
	while (tokens[++i] != NULL)
	{
		if (*tokens[i] == '(')
			count_parentheses++;
		if (*tokens[i] == ')')
			count_parentheses--;
		if (count_parentheses == 0 && (*tokens[i] == '|' || *tokens[i] == '&'))
			break ;
	}
	if (error_parenthesis(count_parentheses, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tokens[i] == NULL)
	{
		tree->content = (t_command *) malloc(sizeof(t_command));
		return (parse_subcmd(tokens[0], tree->content, data, control));
	}
	tree->left = ft_new_node(0, NULL, 0);
	if (parse_command_rec(ft_dsubstr(tokens, 0, i - 1), data, tree->left,
			tokens[i]) == 1)
		return (EXIT_FAILURE);
	tree->right = ft_new_node(0, NULL, 0);
	if (parse_command_rec(&tokens[i + 1], data, tree->right, tokens[i]) == 1)
		return (EXIT_FAILURE);
	if (tokens[i][0] == '|' && tokens[i][1] == '|')
		tree->number = SEMICOLON;
	else if (tokens[i][0] == '&')
		tree->number = AND;
	else
		tree->number = PIPE;
	return (EXIT_SUCCESS);
}

int	parse_command(char *command_str, t_minishell *data)
{
	char		**tokens;
	int			result;

	tokens = split_operands(command_str);
	if (!tokens || error_operands(tokens) == EXIT_FAILURE)
	{
		if (tokens)
			double_free(tokens);
		return (EXIT_FAILURE);
	}
	data->cmd_tree = ft_new_node(0, NULL, 0);
	if (!data->cmd_tree)
		error_init("malloc", 1);
	result = parse_command_rec(tokens, data, data->cmd_tree, NULL);
	double_free(tokens);
	return (result);
}

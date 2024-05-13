/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:48:07 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/10 09:22:30 by yunlovex         ###   ########.fr       */
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

static char	**trim_args(char **tokens, int last_status)
{
	int		i;
	char	**tmp;
	char	**new_token;

	i = 0;
	new_token = 0;
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

static int parse_command_rec(char **tokens, t_minishell *data, int pos, t_tree *tree)
{
	int	count_parentheses;
	int	i;

	count_parentheses = 0;
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (ft_strcmp(tokens[i], "&&") || ft_strcmp(tokens[i], "||"))
			parse_command_rec(ft_dsubstr(tokens), data, pos, tree->right);
	}
	
}

static int parse_command(char *command_str, t_minishell *data, int pos, t_tree **tree)
{
	char	**tokens;
	int		result;

	tokens = split_operands(command_str);
	result = parse_command_rec(tokens, data, pos, tree);
	double_free(tokens);
	return (result);
}

int	parse_subcmd(char *command_str, t_command *cmd, t_minishell *data,
		int pos)
{
	char	**tokens;
	char	*cmd_trimmed;

	cmd_trimmed = ft_strtrim(command_str, " ");
	if (!cmd_trimmed)
		error_init("ft_strtrim", 1);
	tokens = split_command(cmd_trimmed);
	free(cmd_trimmed);
	if (parse_redirect(tokens, cmd, pos, data) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	if (data->status == STOPPED)
	{
		double_free(tokens);
		data->status = RUNNING;
		return (EXIT_FAILURE);
	}
	tokens = trim_args(tokens, data->last_status_cmd);
	if (!tokens)
		error_init("malloc", 1);
	if (parse_command_name(tokens, cmd, data->cmd_list) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	if (parse_args(cmd, tokens) == EXIT_FAILURE)
		return (error_command(cmd, tokens));
	double_free(tokens);
	return (EXIT_SUCCESS);
}

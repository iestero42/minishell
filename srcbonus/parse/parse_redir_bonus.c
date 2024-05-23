/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:21:16 by iestero-          #+#    #+#             */
/*   Updated: 2024/05/17 09:54:16 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_slash5(char *token)
{
	int	i;
	int	slash5_count;
	int	other_count;

	slash5_count = 0;
	other_count = 0;
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '\5')
			slash5_count++;
		else
			other_count++;
	}
	if ((slash5_count > 0 && other_count == 0) || slash5_count == 0)
		return (1);
	else
		return (0);
}

static char	*remove_char(char *token)
{
	char	*tmp;
	char	*before;
	char	*after;
	int		j;

	tmp = token;
	j = 0;
	while (tmp[j] != '\0')
	{
		if (tmp[j] == '\5')
		{
			before = ft_substr(token, 0, j);
			after = ft_substr(token, j + 1, ft_strlen(token) - j - 1);
			tmp = ft_strjoin(before, after);
			free(after);
			j = 0;
		}
		else
			j++;
	}
	return (tmp);
}

static void	rm_slash5(char **token)
{
	int		i;

	i = 0;
	while (token[i] != NULL)
	{
		if (!check_slash5(token[i]))
			token[i] = remove_char(token[i]);
		i++;
	}
}

int	parse_redirect(char **tokens, t_command *cmd, char *control, t_minishell *data)
{
	int	i;

	i = -1;
	cmd->output_redirect = -2;
	cmd->input_redirect = -2;
	rm_slash5(tokens);
	while (tokens[++i] != NULL && data->status != STOPPED)
	{
		if (parse_output(&tokens[i], cmd, control) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (parse_input(&tokens[i], cmd, control, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

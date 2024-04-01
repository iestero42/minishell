/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:47:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/01 12:35:43 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_simple(char **tokens, t_command *cmd,
				int pos, t_minishell *data)
{
	char	*redir;
	char	*tmp;

	redir = ft_strchr(tokens[0], '<');
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->input_redirect);
		tmp = parse_env_variable(&tokens[1], data->last_status_cmd);
		if (*tmp != NULL && !ft_strchr(tmp, '>') && !ft_strchr(tmp, '<'))
		{
			cmd->input_redirect = open(tmp, O_RDONLY, 0644);
			if (cmd->input_redirect < 0)
				perror(tmp);
			free(tmp);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
	}
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//mejorar el parseo de la variale de entorno al meterlo en el here doc
/**
 * @brief 
 * 
 * @param delimiter 
 * @return int 
 */
static int	write_here_doc(char *delimiter, char *filename, int last_status)
{
	char	*line;
	int		here_doc;

	here_doc = open(filename, O_WRONLY | O_CREAT, 0644);
	if (here_doc == -1)
	{
		perror(filename);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(">", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, delimiter, ft_strlen(line) - 1))
	{
		ft_putstr_fd(parse_env_variable(line, last_status), here_doc);
		free(line);
		ft_putstr_fd(">", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(delimiter);
	close(here_doc);
	here_doc = open(filename, O_RDONLY);
	if (here_doc < 0)
		perror(filename);
	return (here_doc);
}

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
static int	open_input_double(char **tokens, t_command *cmd,
				int pos, t_minishell *data)
{
	char	*redir;
	char	*tmp;

	redir = ft_strnstr(tokens[0], "<<", ft_strlen(tokens[0]));
	if (redir)
	{
		if (cmd->input_redirect > -1)
			close(cmd->output_redirect);
		tmp = parse_env_variable(&tokens[1], data->last_status_cmd);
		if (*tmp != NULL && !ft_strchr(tmp, '>')
			&& !ft_strchr(tmp, '<'))
		{
			cmd->input_redirect = write_here_doc(trim_command(tmp),
					cmd->here_doc, data->last_status_cmd);
			*tokens[1] = '\0';
			*tokens[0] = '\0';
		}
		else
			return (error_redir(tmp, tokens[1], pos, data));
	}
	if (cmd->input_redirect == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param token 
 * @param cmd 
 * @param nextToken 
 * @return int 
 */
int	parse_input(char **tokens, t_command *cmd,
		int pos, t_minishell *data)
{
	if (tokens[0][0] != '"' && tokens[0][0] != '\'')
	{
		if (open_input_double(tokens, cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (open_input_simple(tokens, cmd, pos, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

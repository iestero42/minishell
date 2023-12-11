/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:26:50 by marvin            #+#    #+#             */
/*   Updated: 2023/02/08 16:26:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:11:27 by marvin            #+#    #+#             */
/*   Updated: 2022/12/25 10:11:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Function that saves the part of the buffer that not goes in the line
 * in a static string
 * @param stored_lines (char *) that have all the buffer inside
 * @return a static string 
*/
static char	*ft_save(char *stored_lines)
{
	int		i;
	char	*str;

	i = 0;
	while (stored_lines[i] != '\0' && stored_lines[i] != '\n')
		i++;
	if (stored_lines[i] == '\0')
	{
		free(stored_lines);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stored_lines) - i + 1));
	if (!str)
		return (NULL);
	i++;
	ft_strlcpy(str, &stored_lines[i], ft_strlen(stored_lines) - i + 1);
	free(stored_lines);
	return (str);
}

/**
 * Function that find the first line in a buffer 
 * @param stored_lines (char *) all the lines are store in this string
 * @return a string pointing to the line
*/
static char	*ft_lseek(char *stored_lines)
{
	char	*str;
	int		i;

	i = 0;
	if (stored_lines[i] == '\0')
		return (NULL);
	while (stored_lines[i] != '\0' && stored_lines[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, stored_lines, i + 1);
	if (stored_lines[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

/**
 * Fucntion that reads from a file descriptor and store all the reading in a
 * static string
 * @param fd the file descriptor
 * @param stored_lines the string with all the lines
 * @return a string with all the new lines readed
*/
static char	*ft_read(int fd, char *stored_lines)
{
	char	*buf;
	int		readed;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readed = 1;
	while (!ft_strchr(stored_lines, '\n') && readed != '\0')
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		stored_lines = ft_strjoin(stored_lines, buf);
	}
	free(buf);
	return (stored_lines);
}

/**
 * Function that return all the lines one by one from a file
 * @param fd the file descriptor to use in the reading process
*/
char	*get_next_line(int fd)
{
	static char	*stored_lines[256];
	char		*line;

	if (fd < 0 || fd > 255)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (stored_lines[fd]);
		stored_lines[fd] = NULL;
		return (NULL);
	}
	stored_lines[fd] = ft_read(fd, stored_lines[fd]);
	if (!stored_lines[fd])
		return (NULL);
	line = ft_lseek(stored_lines[fd]);
	stored_lines[fd] = ft_save(stored_lines[fd]);
	return (line);
}

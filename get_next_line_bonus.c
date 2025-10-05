/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:15 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/05 09:17:16 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_append(int fd, char *buffer)
{
	char	*temp;
	char	*joined;
	ssize_t	bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (buffer);
	}
	temp[bytes_read] = '\0';
	if (!buffer)
		return (temp);
	joined = ft_strjoin(buffer, temp);
	free(buffer);
	free(temp);
	return (joined);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*buffer);
		if (*temp)
			*buffer = temp;
		else
		{
			free(temp);
			*buffer = NULL;
		}
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	while (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
	{
		temp = read_and_append(fd, buffer[fd]);
		if (temp == buffer[fd])
			break ;
		buffer[fd] = temp;
	}
	if (!buffer[fd] || *buffer[fd] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&buffer[fd]));
}

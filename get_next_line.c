/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:15 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/05 10:37:27 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *buffer)
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
	static char	*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		temp = read_and_join(fd, buffer);
		if (temp == buffer)
			break ;
		buffer = temp;
	}
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}

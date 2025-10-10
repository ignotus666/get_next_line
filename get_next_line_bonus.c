/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:15 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/10 12:16:15 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_join(int fd, char *buffer)
{
	char	*new_data;
	char	*joined;
	ssize_t	bytes_read;

	new_data = malloc(BUFFER_SIZE + 1);
	if (!new_data)
		return (NULL);
	bytes_read = read(fd, new_data, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(new_data);
		return (buffer);
	}
	new_data[bytes_read] = '\0';
	if (!buffer)
		return (new_data);
	joined = ft_strjoin(buffer, new_data);
	free(buffer);
	free(new_data);
	return (joined);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*nl_pos;
	char	*leftover_str;

	nl_pos = ft_strchr(*buffer, '\n');
	if (nl_pos)
	{
		line = ft_substr(*buffer, 0, nl_pos - *buffer + 1);
		leftover_str = ft_strdup(nl_pos + 1);
		free(*buffer);
		if (*leftover_str)
			*buffer = leftover_str;
		else
		{
			free(leftover_str);
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
	char		*updated_buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	while (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
	{
		updated_buff = read_and_join(fd, buffer[fd]);
		if (updated_buff == buffer[fd])
			break ;
		buffer[fd] = updated_buff;
	}
	if (!buffer[fd])
		return (NULL);
	return (extract_line(&buffer[fd]));
}

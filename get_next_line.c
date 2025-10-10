/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:15 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/10 16:06:06 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Read BUFFER_SIZE-d chunks and append them to the currently held data.
Free the old and new_data buffers and the returned (joined) data is updated below
as buffer. If no new data is read (EOF or empty file), return buffer. It will
result in updated_buff == buffer. If it's the first read, just return new_data.
*/

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

/*Look for newline. If found -> extract substring from buffer[0] to nl_pos + 1
							 -> Duplicate leftover data / free old buffer / 
							  assign leftover to buffer.
							  if no leftover
							  	-> Free its assigned memory.
								-> buffer = NULL so next read call starts from 0.
					If no nl -> means read couldn't append data with nl so either
					  			  EOF or empty. Dup and return as line*/

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
	static char	*buffer;
	char		*updated_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		updated_buff = read_and_join(fd, buffer);
		if (updated_buff == buffer)
			break ;
		buffer = updated_buff;
	}
	if (!buffer)
		return (NULL);
	return (extract_line(&buffer));
}

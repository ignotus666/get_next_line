/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:15 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/05 07:28:23 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buff(int fd, char *str_start)
{
	char	*buff;
	char	*joined;
	ssize_t	bytes_rd;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_rd = read(fd, buff, BUFFER_SIZE);
	if (bytes_rd <= 0)
	{
		free(buff);
		return (str_start);
	}
	buff[bytes_rd] = '\0';
	if (str_start != NULL)
	{
		joined = ft_strjoin(str_start, buff);
		free(buff);
		free(str_start);
		return (joined);
	}
	else
		return (buff);
}

char	*ft_fill_buff(int fd, char *str_start)
{
	char	*buffer;
	char	*new_buffer;

	buffer = str_start;
	if (!buffer)
		buffer = read_buff(fd, NULL);
	while (buffer && !ft_strchr(buffer, '\n'))
	{
		new_buffer = read_buff(fd, buffer);
		if (new_buffer == buffer)
			break ;
		buffer = new_buffer;
		if (!buffer)
			break ;
	}
	return (buffer);
}

char	*ft_extract_line(char *whole_buff, char **leftover_start)
{
	char	*nl_found;
	char	*line;

	if (!whole_buff || *whole_buff == '\0')
		return (NULL);
	nl_found = ft_strchr(whole_buff, '\n');
	if (nl_found)
	{
		line = ft_substr(whole_buff, 0, nl_found - whole_buff + 1);
		if (*(nl_found + 1) == '\0')
			*leftover_start = NULL;
		else
			*leftover_start = ft_strdup(nl_found + 1);
	}
	else
	{
		line = ft_strdup(whole_buff);
		*leftover_start = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str_start;
	char		*whole_buff;
	char		*leftover_start;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	whole_buff = ft_fill_buff(fd, str_start);
	if (!whole_buff || *whole_buff == '\0')
	{
		if (str_start)
		{
			free(str_start);
			str_start = NULL;
		}
		if (whole_buff)
			free(whole_buff);
		return (NULL);
	}
	line = ft_extract_line(whole_buff, &leftover_start);
	free(whole_buff);
	str_start = leftover_start;
	return (line);
}

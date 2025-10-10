/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:00:00 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/10 16:44:40 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1, fd2, fd3;
	char	*line;
	int		i;

	fd1 = open("./test_files_bonus/test1.txt", O_RDONLY);
	fd2 = open("./test_files_bonus/test2.txt", O_RDONLY);
	fd3 = open("./test_files_bonus/test3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Error: Could not open one or more test files\n");
		return (1);
	}

	printf("=== Testing Multiple File Descriptors ===\n\n");

	for (i = 0; i < 5; i++)
	{
		printf("--- Round %d ---\n", i + 1);
		line = get_next_line(fd1);
		if (line)
		{
			printf("FD%d: %s", fd1, line);
			free(line);
		}
		else
			printf("FD%d: EOF\n", fd1);
		line = get_next_line(fd2);
		if (line)
		{
			printf("FD%d: %s", fd2, line);
			free(line);
		}
		else
			printf("FD%d: EOF\n", fd2);

		line = get_next_line(fd3);
		if (line)
		{
			printf("FD%d: %s", fd3, line);
			free(line);
		}
		else
			printf("FD%d: EOF\n", fd3);
		printf("\n");
	}
	printf("=== Reading remaining data from FD%d ===\n", fd1);
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("FD%d: %s", fd1, line);
		free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

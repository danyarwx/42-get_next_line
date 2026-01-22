/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhukov <dzhukov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:11:02 by dzhukov           #+#    #+#             */
/*   Updated: 2026/01/22 17:49:42 by dzhukov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

# define BUFFER_SIZE 9


#include "get_next_line.h"
char *get_next_line(int fd)
{
	char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	int bytes_read = read(fd, buffer, BUFFER_SIZE);

	if(bytes_read <= 0)
	{
		printf("Read function failed.\n");
		free(buffer);
		return (NULL);
	}

	buffer[bytes_read] = '\0';
	return(buffer);
}

int main(void)
{

	int fd;
	fd = open("test.txt", O_RDONLY, 0777);

	if (fd < 0)
	{
		printf("File was not created");
		return 1;
	}

	printf("File 'newfile.txt' created successfully \nFile descriptor: %d\n", fd);

	char *str;
	str = get_next_line(fd);

	printf("Read from file : %s\n", str);

	free(str);
	close(fd);
	return (0);
}




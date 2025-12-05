/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhukov <dzhukov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:11:02 by dzhukov           #+#    #+#             */
/*   Updated: 2025/12/05 16:19:23 by dzhukov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
// char *get_next_line(int fd)
// {

// }

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	fd = create("kids.tsx", 0614);

	if (fd == -1)
	{
		printf("File was not created");
		return 1;
	}

	printf("File 'newfile.txt' created successfully \nFile descriptor: %d\n", fd);

	close(fd);
	return (0);
}




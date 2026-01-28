/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhukov <dzhukov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:11:02 by dzhukov           #+#    #+#             */
/*   Updated: 2026/01/28 17:53:54 by dzhukov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		len = i + 1;
	else
		len = i;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

char	*update_stash(char *stash, char *bss)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0' || stash[i + 1] == '\0')
		return (ft_bzero(bss, BUFFER_SIZE + 1), free(stash), NULL);
	i++;
	j = 0;
	while (stash[i] && j < BUFFER_SIZE)
	{
		bss[j] = stash[i];
		j++;
		i++;
	}
	ft_bzero(bss + j, BUFFER_SIZE - j - 1);
	free(stash);
	return (bss);
}

char	*read_stash(int fd, char *stash)
{
	char	*temp;
	int		bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (ft_strchr(stash, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (stash = NULL, NULL);
		}
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (!stash)
			return (free(buffer), NULL);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	bss[BUFFER_SIZE + 1];
	char		*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_strdup(bss);
	if (!stash)
		return (NULL);
	stash = read_stash(fd, stash);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = update_stash(stash, bss);
	return (line);
}

// int main(void)
// {
//     int fd;
//     char *line;
//     int count = 1;

//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         printf("Error opening file\n");
//         return (1);
//     }

//     // Read all lines
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("Line %d: %s", count, line);
//         free(line);
//         count++;
//     }

//     close(fd);

// }
//
// We have a file with multiple lines:

// Line One\n
// Line Two\n
// Line Three\n

// And the buffer with size 5

// How get next line works:

// The main function reads the file with a given buffer and puts it
// into a string buffer
// buffer gets overwritten with each call.
// Now we uppend each of the read outputs into another string called stash,
// using ft_strjoin and freeing the previous stash all the time.
// And with each iteration we check whether or not this stash contains '\n'

// As soon as newline is inside the string, we stop the loop,
// we free the buffer,
// and we return the stash containing either just our first string
// or a little more.

// Next step is to extract the exact line we need.
// with the extract_line function
// we allocate memory and make a copy of the string just till
// the newline symbol
// or till end of string is reached, this is stored in "line".

// Next step is to update stash in case we have something left.
// Here we basically
// make another stash and copy there from the newline

// if (stash[i] == '\0')
// {
//     free(stash);
//     return (NULL);
// }
// ```

// What it does:
// - Check if there's any content after the `\n`
// - If the character right after `\n` is `\0`, we've extracted everything

// Example 1**: `stash = "OneLine\n"`
// ```
// Index: 0 1 2 3 4 5 6 7 8
// Char:  O n e L i n e \n \0

// After i++: i = 8
// Check: stash[8] == '\0'? → YES

// Action:
//   1. free(stash) → release memory
//   2. return NULL → nothing left
// ```

// We either update stash by copying everything after the newline, or we check
// and if there is not anything after the newline or EOF is reached,
// we free stash and return NULL;

// Finally we return the line that was read.
// If we run get next line again, the leftovers are stored
// in the static variable
// stash and we are going to print them out next time.

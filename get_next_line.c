/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhukov <dzhukov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:11:02 by dzhukov           #+#    #+#             */
/*   Updated: 2026/01/25 16:36:08 by dzhukov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"
# define BUFFER_SIZE 5


char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}


size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	i;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	ptr = (char *)malloc((len1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		ptr[i + len1] = s2[i];
		i++;
	}
	ptr[i + len1] = '\0';
	return (ptr); // Returns allocated string
}




char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	dup = (char *)malloc(len * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}



char	*extract_line(char *stash)
{
	//Return the line till \n or the full line if no \n
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


char	*update_stash(char *stash)
{
	char *new;
	size_t i;
	size_t j;

	i = 0;
	while(stash[i] && stash[i] != '\n')
		i++;

	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	i++;

	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}


	new = malloc(sizeof(char) * (ft_strlen(stash + i) + 1)); // allocate memory for whats left

	if (!new)
		return(free(stash), NULL);

	j = 0;
	while(stash[i])
	{
		new[j] = stash[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(stash);
	return(new);
}

char *read_stash(int fd, char *stash)
{
	char *temp;
	int bytes_read;
	char *buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	bytes_read = 1;
	while (ft_strchr(stash, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if(bytes_read <= 0)
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
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return(stash);
}

char *get_next_line(int fd)
{
	static char *stash;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup(""); // Empty string so the while loop works
	if (!stash)
		return (NULL);

	stash = read_stash(fd, stash);
	if (!stash)
		return (NULL);

	line = extract_line(stash);
	stash = update_stash(stash);
	return(line);
}


int main(void)
{
    int fd;
    char *line;
    int count = 1;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return (1);
    }

    // Read all lines
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", count, line);
        free(line);
        count++;
    }

    close(fd);

}



/*

We have a file with multiple lines:

Line One\n
Line Two\n
Line Three\n

And the buffer with size 5

How get next line works:

The main function reads the file with a given buffer and puts it into a string buffer
Now we uppend each of the read outputs into another string called stash
And with each iteration we check





*/

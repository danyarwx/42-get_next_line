/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhukov <dzhukov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:11:02 by dzhukov           #+#    #+#             */
/*   Updated: 2026/01/25 12:44:07 by dzhukov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"
# define BUFFER_SIZE 3


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




char *get_next_line(int fd)
{
	static char *stash;
	char *temp;
	int bytes_read;
	char *buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup(""); // Empty string so the while loop works


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
	}

	free(buffer);
	return(stash);
}





int main(void)
{
	int fd;
	char *result;
	fd = open("test.txt", O_RDONLY, 0777);

	if (fd < 0)
	{
		printf("File was not created");
		return 1;
	}

    // Test 1: First call
    result = get_next_line(fd);
    printf("Call 1: %s\n", result);
    // Note: We don't free 'result' here yet because it IS the static 'stash'
    // In the real project, you'd return a COPY and free the result.

    // Test 2: Second call
    result = get_next_line(fd);
    printf("Call 2: %s\n", result);

    close(fd);
	return (0);
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/21 16:22:10 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*remainder)
		*remainder = allocate_string(0);
	return (1);
}

static int	read_update_remainder(int fd, char **remainder)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free(temp);
		if (!*remainder)
			return (-1);
	}
	free(buffer);
	return (bytes_read);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

static char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		temp = *remainder;
		*remainder = ft_substr(*remainder, newline_pos - *remainder + 1,
				ft_strlen(*remainder));
		free(temp);
		if (**remainder == '\0')
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
	{
		line = allocate_string(ft_strlen(*remainder));
		if (!line)
			return (NULL);
		ft_memcpy(line, *remainder, ft_strlen(*remainder));
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	int			bytes_read;

	if (check_errors(fd, &remainder) != 1)
		return (NULL);
	bytes_read = read_update_remainder(fd, &remainder);
	if (bytes_read == -1)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (bytes_read == 0 && (!remainder || *remainder == '\0'))
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder);
	return (line);
}

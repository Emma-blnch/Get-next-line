/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:03:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/22 10:21:10 by eblancha         ###   ########.fr       */
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
			break ;
		buffer[bytes_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free(temp);
		if (!*remainder)
		{
			bytes_read = -1;
			break ;
		}
	}
	free(buffer);
	return (bytes_read);
}

static char	*update_remainder(char **remainder, char *newline_pos)
{
	char	*temp;
	char	*new_remainder;

	temp = *remainder;
	if (newline_pos)
	{
		new_remainder = allocate_string(ft_strlen(newline_pos + 1));
		if (new_remainder)
			ft_strlcpy(new_remainder, newline_pos + 1,
				ft_strlen(newline_pos + 1) + 1);
	}
	else
		new_remainder = NULL;
	free(temp);
	return (new_remainder);
}

static char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
		len = newline_pos - *remainder + 1;
	else
		len = ft_strlen(*remainder);
	line = allocate_string(len);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *remainder, len + 1);
	*remainder = update_remainder(remainder, newline_pos);
	if (!*remainder || **remainder == '\0')
	{
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

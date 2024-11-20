/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/20 12:20:45 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
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
	while (!ft_strchr(remainder[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer)
			return (-1);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = remainder[fd];
		remainder[fd] = ft_strjoin(remainder[fd], buffer);
		free(temp);
		if (!remainder[fd])
			return (-1);
	}
	free(buffer);
	return (bytes_read);
}

static char	*extract_line(int fd, char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	newline_pos = ft_strchr(remainder[fd], '\n');
	if (newline_pos)
	{
		line = ft_substr(remainder[fd], 0, newline_pos - remainder[fd] + 1);
		temp = remainder[fd];
		remainder[fd] = ft_substr(remainder[fd],
				newline_pos - remainder[fd] + 1, ft_strlen(remainder[fd]));
		free(temp);
		if (*remainder[fd] == '\0')
		{
			free(remainder[fd]);
			remainder[fd] = NULL;
		}
	}
	else
	{
		line = ft_strdup(remainder[fd]);
		free(remainder[fd]);
		remainder[fd] = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	int			bytes_read;

	if (check_errors(fd, remainder) != 1)
		return (NULL);
	bytes_read = read_update_remainder(fd, remainder);
	if (bytes_read == -1)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	if (bytes_read == 0 && (!remainder[fd] || *remainder[fd] == '\0'))
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	line = extract_line(fd, remainder);
	return (line);
}

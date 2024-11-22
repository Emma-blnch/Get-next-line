/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_commented.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/22 14:11:05 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* *
 same logic as in get_next_line but we have to handle multiple fd so instead of using *remainder we use remainder[fd] to have each fd as parameter
 * */

static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (!remainder[fd])
		remainder[fd] = allocate_string(0);
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
		if (bytes_read <= 0)
		{
			free(buffer);
			return (0);
		}
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

static char	*update_remainder(int fd, char **remainder, char *newline_pos)
{
	char	*temp;
	char	*new_remainder;

	temp = remainder[fd];
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

static char	*extract_line(int fd, char **remainder)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(remainder[fd], '\n');
	if (newline_pos)
		len = newline_pos - remainder[fd] + 1;
	else
		len = ft_strlen(remainder[fd]);
	line = allocate_string(len);
	if (!line)
		return (NULL);
	ft_strlcpy(line, remainder[fd], len + 1);
	remainder[fd] = update_remainder(fd, remainder, newline_pos);
	if (!remainder[fd] || *remainder[fd] == '\0')
	{
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

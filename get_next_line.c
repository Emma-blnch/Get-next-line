/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/19 14:19:50 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*remainder)
		*remainder = ft_strdup("");
	return (1);
}

static int	read_update_remainder(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (!ft_strchr(*remainder, '\n') && (bytes_read > 0))
	{
		buffer[bytes_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free(temp);
		if (!*remainder)
			return (-1);
	}
	return (bytes_read);
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
		free (temp);
	}
	else
	{
		line = ft_strdup(*remainder);
		free (*remainder);
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
	if (bytes_read <= 0 || (!remainder || *remainder == '\0')
		|| bytes_read == -1)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder);
	return (line);
}

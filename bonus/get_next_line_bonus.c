/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/03 09:44:07 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_errors(int fd, char **stored_lines)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (!stored_lines[fd])
		stored_lines[fd] = allocate_string(0);
	return (1);
}

static int	read_and_store_lines(int fd, char **stored_lines)
{
	char	*current_read_chunk;
	char	*temporary;
	int		bytes_read;

	bytes_read = 0;
	current_read_chunk = malloc(BUFFER_SIZE + 1);
	if (!current_read_chunk)
		return (-1);
	while (!ft_strchr(stored_lines[fd], '\n'))
	{
		bytes_read = read(fd, current_read_chunk, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		current_read_chunk[bytes_read] = '\0';
		temporary = stored_lines[fd];
		stored_lines[fd] = ft_strjoin(stored_lines[fd], current_read_chunk);
		free(temporary);
		if (!stored_lines[fd])
		{
			free(current_read_chunk);
			return (-1);
		}
	}
	free(current_read_chunk);
	return (bytes_read);
}

static char	*update_stored_lines(int fd, char **stored_lines, char *newline_pos)
{
	char	*new_stored_lines;
	size_t	length;

	if (newline_pos)
	{
		length = ft_strlen(newline_pos + 1);
		new_stored_lines = allocate_string(length);
		if (new_stored_lines)
			ft_strlcpy(new_stored_lines, newline_pos + 1, length + 1);
	}
	else
		new_stored_lines = NULL;
	free(stored_lines[fd]);
	return (new_stored_lines);
}

static char	*extract_line(int fd, char **stored_lines)
{
	char	*newline_position;
	char	*line;
	size_t	length;

	newline_position = ft_strchr(stored_lines[fd], '\n');
	if (newline_position)
		length = newline_position - stored_lines[fd] + 1;
	else
		length = ft_strlen(stored_lines[fd]);
	line = allocate_string(length);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stored_lines[fd], length + 1);
	stored_lines[fd] = update_stored_lines(fd, stored_lines, newline_position);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stored_lines[1024];
	char		*line;
	int			bytes_read;

	if (check_errors(fd, stored_lines) != 1)
		return (NULL);
	bytes_read = read_and_store_lines(fd, stored_lines);
	if (bytes_read == -1 || (bytes_read == 0
			&& (!stored_lines[fd] || *stored_lines[fd] == '\0')))
	{
		free(stored_lines[fd]);
		stored_lines[fd] = NULL;
		return (NULL);
	}
	line = extract_line(fd, stored_lines);
	return (line);
}

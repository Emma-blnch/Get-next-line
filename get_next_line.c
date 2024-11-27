/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:03:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/27 10:36:50 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_errors(int fd, char **stored_lines)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*stored_lines)
		*stored_lines = allocate_string(0);
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
	while (!ft_strchr(*stored_lines, '\n'))
	{
		bytes_read = read(fd, current_read_chunk, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		current_read_chunk[bytes_read] = '\0';
		temporary = *stored_lines;
		*stored_lines = ft_strjoin(*stored_lines, current_read_chunk);
		free(temporary);
		if (!*stored_lines)
		{
			bytes_read = -1;
			break ;
		}
	}
	free(current_read_chunk);
	return (bytes_read);
}

static char	*update_stored_lines(char **stored_lines, char *newline_position)
{
	char	*temporary;
	char	*new_stored_lines;

	temporary = *stored_lines;
	if (newline_position)
	{
		new_stored_lines = allocate_string(ft_strlen(newline_position + 1));
		if (new_stored_lines)
			ft_strlcpy(new_stored_lines, newline_position + 1,
				ft_strlen(newline_position + 1) + 1);
	}
	else
		new_stored_lines = NULL;
	free(temporary);
	return (new_stored_lines);
}

static char	*extract_line(char **stored_lines)
{
	char	*newline_position;
	char	*line;
	size_t	length;

	newline_position = ft_strchr(*stored_lines, '\n');
	if (newline_position)
		length = newline_position - *stored_lines + 1;
	else
		length = ft_strlen(*stored_lines);
	line = allocate_string(length);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *stored_lines, length + 1);
	*stored_lines = update_stored_lines(stored_lines, newline_position);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stored_lines;
	char		*line;
	int			bytes_read;

	if (check_errors(fd, &stored_lines) != 1)
		return (NULL);
	bytes_read = read_and_store_lines(fd, &stored_lines);
	if (bytes_read == -1)
	{
		free(stored_lines);
		stored_lines = NULL;
		return (NULL);
	}
	if (bytes_read == 0 && (!stored_lines || *stored_lines == '\0'))
	{
		free(stored_lines);
		stored_lines = NULL;
		return (NULL);
	}
	line = extract_line(&stored_lines);
	return (line);
}

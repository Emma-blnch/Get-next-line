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

static int	check_errors(int fd, char **storedLines)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*storedLines)
		*storedLines = allocate_string(0);
	return (1);
}

static int	read_and_store_lines(int fd, char **storedLines)
{
	char	*currentReadChunk;
	char	*temporary;
	int		bytesRead;

	bytesRead = 0;
	currentReadChunk = malloc(BUFFER_SIZE + 1);
	if (!currentReadChunk)
		return (-1);
	while (!ft_strchr(*storedLines, '\n'))
	{
		bytesRead = read(fd, currentReadChunk, BUFFER_SIZE);
		if (bytesRead <= 0)
			break ;
		currentReadChunk[bytesRead] = '\0';
		temporary = *storedLines;
		*storedLines = ft_strjoin(*storedLines, currentReadChunk);
		free(temporary);
		if (!*storedLines)
		{
			bytesRead = -1;
			break ;
		}
	}
	free(currentReadChunk);
	return (bytesRead);
}

static char	*update_storedLines(char **storedLines, char *newlinePosition)
{
	char	*temporary;
	char	*new_storedLines;

	temporary = *storedLines;
	if (newlinePosition)
	{
		new_storedLines = allocate_string(ft_strlen(newlinePosition + 1));
		if (new_storedLines)
			ft_strlcpy(new_storedLines, newlinePosition + 1,
				ft_strlen(newlinePosition + 1) + 1);
	}
	else
		new_storedLines = NULL;
	free(temporary);
	return (new_storedLines);
}

static char	*extract_line(char **storedLines)
{
	char	*newlinePosition;
	char	*line;
	size_t	length;

	newlinePosition = ft_strchr(*storedLines, '\n');
	if (newlinePosition)
		length = newlinePosition - *storedLines + 1;
	else
		length = ft_strlen(*storedLines);
	line = allocate_string(length);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *storedLines, length + 1);
	*storedLines = update_storedLines(storedLines, newlinePosition);
	/*if (!*storedLines || **storedLines == '\0')
	{
		free(*storedLines);
		*storedLines = NULL;
	}*/
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storedLines;
	char		*line;
	int			bytesRead;

	if (check_errors(fd, &storedLines) != 1)
		return (NULL);
	bytesRead = read_and_store_lines(fd, &storedLines);
	if (bytesRead == -1)
	{
		free(storedLines);
		storedLines = NULL;
		return (NULL);
	}
	if (bytesRead == 0 && (!storedLines || *storedLines == '\0'))
	{
		free(storedLines);
		storedLines = NULL;
		return (NULL);
	}
	line = extract_line(&storedLines);
	return (line);
}

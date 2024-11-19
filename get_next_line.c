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

	while (!ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) //si read échoue
		{
			write(2, "error: read failed\n", 19);
			return (-1);
		}
		if (bytes_read == 0) //fin du fichier
		{
			write(2, "end of file reached\n", 21);
			break ;
		}
		buffer[bytes_read] = '\0';

		write(2, "buffer read: ", 13);
		write(2, buffer, bytes_read);
		write(2, "\n", 1);

		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);

		write(2, "Remainder updated: ", 19);
		write(2, *remainder, ft_strlen(*remainder));
		write(2, "\n", 1);

		free(temp);
		if (!*remainder)
		{
			write(2, "Error: memory allocation failed\n", 32);
			return (-1);
		}
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
		
		write(2, "Extracted line: ", 16);
		write(2, line, ft_strlen(line));
		write(2, "\n", 1);

		temp = *remainder;
		*remainder = ft_substr(*remainder, newline_pos - *remainder + 1,
				ft_strlen(*remainder));
		free (temp);
	}
	else
	{
		line = ft_strdup(*remainder);
		
		write(2, "Last extracted line: ", 21);
		write(2, line, ft_strlen(line));
		write(2, "\n", 1);
		
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

	write(2, "Entering get_next_line\n", 23);

	if (check_errors(fd, &remainder) != 1)
	{
		write(2, "Error: invalid input\n", 21);		
		return (NULL);
	}
	bytes_read = read_update_remainder(fd, &remainder);
	if (bytes_read == -1)
	{
		write(2, "Error: read_update_remainder failed\n", 35);
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (bytes_read == 0 && (!remainder || *remainder == '\0'))
	{
		write(2, "End of file with empty remainder\n", 33);
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder);

	write(2, "Returning line: ", 16);
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);

	return (line);
}

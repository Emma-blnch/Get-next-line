/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_commented.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/21 16:06:02 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// check initial errors and initialize remainder
static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || BUFFER_SIZE <= 0) // check if fd and BUFFER_SIZE are valid
		return (0);
	if (!*remainder) // if remainder is empty
		*remainder = ft_strdup(""); // I initialize it with an empty string
	return (1); // 1 to indicate the success of verifications
}

// read data and update remainder
static int	read_update_remainder(int fd, char **remainder)
{
	char	*buffer; // buffer to read the file
	char	*temp; // temporary variable to manipulate remainder
	int		bytes_read; // store bytes I read

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE + 1); // dynamic memory allocation
	if (!buffer)
		return (-1); // check if memory allocation went ok
	while (!ft_strchr(*remainder, '\n')) // continue to read as long as I don't have a \n
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); // I read BUFFER_SIZE bytes from fd in buffer
		if (bytes_read <= 0) // if reading fails or if end of file is reached
		{
			free(buffer); // to avoid memory leaks
			return (0);
		}
		buffer[bytes_read] = '\0'; // I convert buffer into a string
		temp = *remainder; // I store re;ainder in temp
		*remainder = ft_strjoin(*remainder, buffer); // I combine remainder and buffer into a new string
		free(temp); // I free previous memory of remainder
		if (!*remainder) // if allocation fails
			return (-1);
	}
	free(buffer); // very important to avoid leaks
	return (bytes_read); // I return the number of bytes read
}

// extract one complete line from remainder
static char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	newline_pos = ft_strchr(*remainder, '\n'); // I search for the first \n in remainder
	if (newline_pos) // if I find it
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1); // I extract the line (including the \n)
		temp = *remainder;
		*remainder = ft_substr(*remainder, newline_pos - *remainder + 1,
				ft_strlen(*remainder)); // I update remainder with the characters afte \n
		free(temp); // I free the old value of remainder
		if (**remainder == '\0') // if after the extraction remainder is empty
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else // if no \n
	{
		line = *remainder; // I duplicate remainder in line
		free(*remainder); // and free remainder
		*remainder = NULL;
	}
	return (line); // I return the extracted line
}

// main function
char	*get_next_line(int fd)
{
	static char	*remainder; // store remaining bytes after a line has been extracted
	char		*line;
	int			bytes_read;

	if (check_errors(fd, &remainder) != 1) // check if fd and BUFFER_SIZE are valid 
		return (NULL); // if error I return NULL
	bytes_read = read_update_remainder(fd, &remainder); // I read the content of the file and add the characters read in remainder
	if (bytes_read == -1) // -1 means error when storing the number of bytes read in our variable
	{
		free(remainder); // I free remainder
		remainder = NULL; // I reset it to NULL
		return (NULL);
	}
	if (bytes_read == 0 && (!remainder || *remainder == '\0')) // if end of file or if remainder is empty
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder);
	return (line); // I return the extracted line
}

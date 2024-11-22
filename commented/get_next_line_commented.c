/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_commented.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:03:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/22 14:09:53 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// check initial erros and initialize remainder
static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || BUFFER_SIZE <= 0) // check if fd and BUFFER_SIZE are valid
		return (0);
	if (!*remainder) // if remainder is empty
		*remainder = allocate_string(0); // I initialise it to an empty string
	return (1); // 1 to indicate the success of the verifications
}

// read data and update remainder
static int	read_update_remainder(int fd, char **remainder)
{
	char	*buffer; // buffer to read file
	char	*temp; // temporary variable to manipulate remainder
	int		bytes_read; // store bytes read

	bytes_read = 0; // initialize to 0 to avoid mistakes
	buffer = malloc(BUFFER_SIZE + 1); // dynamic memory allocation
/* if you do static allocation your program will have trouble when BUFFER_SIZE is big (like 10000000 for example)*/

	if (!buffer)
		return (-1); // check if memory allocation went ok
	while (!ft_strchr(*remainder, '\n')) // continue to read as long as I don't have a '\n'
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); // I read BUFFER_SIZE bytes from fd in buffer
		if (bytes_read <= 0) // if reading fails or end of file is reached
			break ; // stop everything
		buffer[bytes_read] = '\0'; // convert buffer into a string
		temp = *remainder; // store remainder in temp
		*remainder = ft_strjoin(*remainder, buffer); // combine remainder and buffer into a new string
		free(temp); // free previous memory of remainder
		if (!*remainder) // if allocation fails
		{
			bytes_read = -1; // ?
			break ;
		}
	}
	free(buffer); // very important to avoid leaks
	return (bytes_read); // return the number of bytes read
}

// update remainder after each line extraction
static char	*update_remainder(char **remainder, char *newline_pos)
{
	char	*temp;
	char	*new_remainder; // new remainder after a line has been extracted

	temp = *remainder; // store remainder in temp
	if (newline_pos) // if I found a '\n' in extract_line
	{
		new_remainder = allocate_string(ft_strlen(newline_pos + 1));
		if (new_remainder)
			ft_strlcpy(new_remainder, newline_pos + 1,
				ft_strlen(newline_pos + 1) + 1);
	}
	else // if no '\n' was found in extract_line
		new_remainder = NULL; // then I don't need a new remainder
	free(temp);
	return (new_remainder); // return the new remainder with everything but the extracted line
}

// extract one line from remainder
static char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(*remainder, '\n'); //search for the first '\n' in remainder
	if (newline_pos) // if I find it
		len = newline_pos - *remainder + 1; // extract everything in remainder until the '\n'
	else // if no '\n'
		len = ft_strlen(*remainder); // the line is everything in remainder
	line = allocate_string(len); // allocate enough memory for the line found
	if (!line) // if allocation fails
		return (NULL);
	ft_strlcpy(line, *remainder, len + 1); // copy remainder in line
	*remainder = update_remainder(remainder, newline_pos); // update remainder without the line just found
	if (!*remainder || **remainder == '\0') // if after the extraction remainder is empty
	{
		free(*remainder); // free memory
		*remainder = NULL; // reset remainder to NULL
	}
	return (line); // return the extracted line
}

// main function
char	*get_next_line(int fd)
{
	static char	*remainder; // store remaining bytes after a line has been extracted
	char		*line;
	int			bytes_read;

	if (check_errors(fd, &remainder) != 1) // check if fd and BUFFER_SIZE are valid
		return (NULL);
	bytes_read = read_update_remainder(fd, &remainder); // read the content of the file and add characters read in remainder
	if (bytes_read == -1) // if error when storing the number of bytes read
	{
		free(remainder); // free memory
		remainder = NULL; // reset remainder to NULL
		return (NULL);
	}
	if (bytes_read == 0 && (!remainder || *remainder == '\0')) // if end of file or if remainder is empty
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder); // extract the line from remainder
	return (line); // return the extracted line
}

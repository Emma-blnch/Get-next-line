#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder; // Stocke les données résiduelles
	char	buffer[BUFFER_SIZE + 1]; // Tampon pour les données lues
	char	*line; // Contient la ligne a retourner
	char	*temp;
	char	*newline_pos;
	int		bytes_read; // Nombre d’octets lus

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	while (!ft_strchr(remainder, '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		temp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(temp);
	}
	if (bytes_read <= 0 || (!remainder || *remainder == '\0'))
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(remainder, 0, newline_pos - remainder + 1);
		temp = remainder;
		remainder = ft_substr(remainder, newline_pos - remainder + 1, ft_strlen(remainder));
		free (temp);
	}
	else
	{
		line = ft_strdup(remainder);
		free (remainder);
		remainder = NULL;
	}
	return (line);
}

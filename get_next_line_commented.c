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
// check erreurs initiales et initialise remainder
static int	check_errors(int fd, char **remainder)
{
	if (fd < 0 || BUFFER_SIZE <= 0) // check si fd valide et BUFFER_SIZE aussi
		return (0);
	if (!*remainder) // si remainder vide
		*remainder = ft_strdup(""); // je l'initialise avec une chaine vide
	return (1); // j'indique que les verifications ont reussi
}
// lit données et met a jour remainder
static int	read_update_remainder(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1]; // tampon pour lire le fichier
	char	*temp; // temporaire pour manipuler remainder
	int		bytes_read; // stocke octets lus

	bytes_read = 0;
	while (!ft_strchr(*remainder, '\n')) // continue a lire tant que je n'ai pas \n
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); // je lis BUFFER_SIZE octets depuis fd dans buffer
		if (bytes_read == -1) // si la lecture echoue
			return (-1);
		if (bytes_read == 0) // si la fin du fichier est atteinte
			break ; // j'arrete la boucle
		buffer[bytes_read] = '\0'; // je transforme buffer en string
		temp = *remainder; // je stocke remainder dans temp
		*remainder = ft_strjoin(*remainder, buffer); // je combine remainder et buffer dans une nouvelle chaine
		free(temp); // je libere l'ancienne memoire de remainder
		if (!*remainder) // si l'allocation echoue
			return (-1); // je retourne -1
	}
	return (bytes_read); // retourne nb octets lus
}
// extrait une ligne complete depuis remainder
static char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	newline_pos = ft_strchr(*remainder, '\n'); // recherche premier \n dans remainder
	if (newline_pos) // si je le trouve
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1); // j'extrait la ligne jusqu'au \n inclue
		temp = *remainder;
		*remainder = ft_substr(*remainder, newline_pos - *remainder + 1,
				ft_strlen(*remainder)); // je maj remainder avec les cara apres \n
		free(temp); // je libere l'ancienne valeur de remainder
		if (**remainder == '\0') // s'il devient vide apres extraction
		{
			free(*remainder); // je libere sa memoire
			*remainder = NULL; // et je le met a NULL
		}
	}
	else // si aucun \n
	{
		line = ft_strdup(*remainder); // je copie remainder dans line (car que 1 ligne dans fd)
		free(*remainder); // je libere
		*remainder = NULL; // et met à NULL
	}
	return (line); // je retourne la ligne extraite
}
// fonction principale qui appelle les autres
char	*get_next_line(int fd)
{
	static char	*remainder; // stocke caracteres restant apres extraction d'une ligne
	char		*line;
	int			bytes_read; // octets lus

	if (check_errors(fd, &remainder) != 1) // check si fd est valide et BUFFEZ_SIZE correcte 
					       // + initialise remainder si NULL
		return (NULL); // si erreur je retourne NULL
	bytes_read = read_update_remainder(fd, &remainder); // je lis le contenu du fichier et ajoute les caracteres lus a remainder
	if (bytes_read == -1) // stocke nb octets lus dans bytes read ou -1 si erreur
	{
		free(remainder); // je free remainder
		remainder = NULL; // le reinitialise a NULL
		return (NULL); // et retourne NULL
	}
	if (bytes_read == 0 && (!remainder || *remainder == '\0')) // si fin du fichier OU remainder est vide
	{
		free(remainder); //same
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(&remainder); // j'extrait une ligne de remainder jusque \n et met a jour rremainder avec caracteres restants
	return (line); // je retourne la ligne extraite
}

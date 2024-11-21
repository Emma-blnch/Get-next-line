/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:31 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/20 12:17:21 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd1, fd2, fd3;
	char	*line1, *line2, *line3;;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY); 
	if (argc < 2)
		return (0);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		write(2, "Error opening file", 18);
		return (1);
	}
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	printf("File 1 : %s\n", line1);
	printf("File 2 : %s\n", line2);
	printf("File 3 : %s\n", line3);
	
	free(line1);
	free(line2);
	free(line3);
	
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:03:37 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/27 11:14:10 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *string, int character);
size_t	ft_strlen(char *string);
size_t	ft_strlcpy(char *dest, const char *source, size_t dest_size);
char	*ft_strjoin(char *string1, char *string2);
char	*allocate_string(size_t size);

#endif

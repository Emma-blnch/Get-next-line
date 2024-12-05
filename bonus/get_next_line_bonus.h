/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:51:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/22 10:36:22 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *string, int character);
size_t	ft_strlen(char *string);
char	*ft_strjoin(char *s1, char *s2);
char	*allocate_string(size_t size);
size_t	ft_strlcpy(char *dest, const char *source, size_t dest_size);

#endif

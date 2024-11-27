/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:03:54 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/27 11:13:26 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *string)
{
	size_t	index;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
		index++;
	return (index);
}

char	*allocate_string(size_t size)
{
	char	*result;

	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (allocate_string(0));
	s1_len = 0;
	s2_len = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[s1_len])
	{
		result[s1_len] = s1[s1_len];
		s1_len++;
	}
	while (s2[s2_len])
	{
		result[s1_len + s2_len] = s2[s2_len];
		s2_len++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}

char	*ft_strchr(const char *string, int character)
{
	int	index;

	if (!string)
		return (NULL);
	index = 0;
	while (string[index])
	{
		if (string[index] == (char)character)
			return ((char *)(string + index));
		index++;
	}
	if (string[index] == (char)character)
		return ((char *)(string + index));
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *source, size_t dest_size)
{
	size_t	index;

	if (!source)
		return (0);
	if (dest_size == 0)
		return (ft_strlen((char *)source));
	index = 0;
	if (dest_size > 0)
	{
		while (source[index] && index < dest_size - 1)
		{
			dest[index] = source[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (ft_strlen((char *)source));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:43 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/22 10:38:21 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *string)
{
	int	index;

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
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

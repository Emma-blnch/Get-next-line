/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:52:43 by eblancha          #+#    #+#             */
/*   Updated: 2024/11/18 15:54:19 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t i;
    size_t j;
    char *result;

    i = 0;
    j = 0;
    result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!result)
        return (NULL);
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';
    return (result);
}

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *pointer;
    size_t i;

    i = 0;
    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;
    pointer = malloc(sizeof(char) * len + 1);
    if (!pointer)
        return (NULL);
    while (i < len && s[start + i])
    {
        pointer[i] = s[start + i];
        i++;
    }
    pointer[i] = '\0';
    return (pointer);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char    *ft_strdup(char *s)
{
        size_t  i;
        char    *dup;

        i = 0;
        dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
        if (!dup)
                return (NULL);
        while (s[i])
        {
                dup[i] = s[i];
                i++;
        }
        dup[i] = '\0';
        return (dup);
}

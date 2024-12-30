/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:01:42 by aouaalla          #+#    #+#             */
/*   Updated: 2024/12/02 22:01:43 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*p;
	size_t	total_len;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup((char *)s2));
	else if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc((total_len + 1) * sizeof(char));
	if (!p)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	while (i < j)
		p[i++] = *s1++;
	j = 0;
	while (i < total_len)
	{
		p[i] = s2[j++];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*p;
	size_t	i;

	p = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!p)
		return (p);
	i = 0;
	while (*str)
		p[i++] = *str++;
	p[i] = '\0';
	return (p);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		return (ft_strdup((char *)(s + start)));
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (p);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:59 by aouaalla          #+#    #+#             */
/*   Updated: 2024/12/02 22:04:00 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clear(char **p)
{
	free(*p);
	*p = NULL;
}

static char	*init(int fd, char *s, char *buffer)
{
	char	*tmp;
	int		i;

	i = 1;
	while (i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (clear(&buffer), buffer);
		buffer[i] = '\0';
		tmp = s;
		s = ft_strjoin(tmp, buffer);
		clear(&tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (s);
}

static char	*untill_nline(char *str)
{
	size_t	len;

	len = 0;
	if (*str == '\n')
		return (ft_substr(str, 0, 1));
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	return (ft_substr(str, 0, len));
}

static char	*after_nline(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '\n');
	if (!tmp)
		return (tmp);
	tmp++;
	return (ft_strdup(tmp));
}

char	*get_next_line(int fd)
{
	static char	*st[OPEN_MAX];
	char		*p;
	char		*container;
	char		*line;

	p = NULL;
	if (fd < 0 || BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	p = (char *)malloc(((BUFFER_SIZE + 1)) * sizeof(char));
	if (!p)
		return (p);
	container = init(fd, st[fd], p);
	if (!container)
		return (clear(&st[fd]), st[fd]);
	st[fd] = after_nline(container);
	line = untill_nline(container);
	clear(&p);
	clear(&container);
	return (line);
}

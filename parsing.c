/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:07:28 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/06 10:07:29 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static int	get_map_width(int fd, t_gl *gl_ptr)
{
	int		i;
	int		j;
	char	*tmp;

	gl_ptr->map_width = malloc(gl_ptr->height * sizeof(t_map));
	if (!gl_ptr->map_width)
		return (write(2, "error: malloc failure!", 22), 1);
	j = -1;
	tmp = get_next_line(fd);
	while (tmp)
	{
		gl_ptr->map_width[++j].width = 0;
		i = -1;
		while (tmp[++i])
		{
			if ((tmp[i] != ' ' && tmp[i] != '\n') && (tmp[i + 1] == '\n'
					|| tmp[i + 1] == ' ' || tmp[i + 1] == '\0'))
				gl_ptr->map_width[j].width++;
		}
		free(tmp);
		tmp = get_next_line(fd);
	}
	close (fd);
	return (0);
}

static int	check_valid(t_gl *gl_ptr)
{
	int	i;

	i = 0;
	while (i < gl_ptr->height)
	{
		if (gl_ptr->map_width[0].width != gl_ptr->map_width[i].width)
			return (write(2, "error: invalid map!", 19), 1);
		i++;
	}
	return (0);
}

static void	fill_matrix(char *line, t_map *arr, t_gl *data_ptr)
{
	int		i;
	int		j;
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return ;
	i = -1;
	while (++i < (*data_ptr).width)
	{
		arr[i].z = ft_atoi(line_splitted[i]);
		if (ft_strchr(line_splitted[i], ','))
		{
			j = 0;
			while (line_splitted[i][j] && line_splitted[i][j] != ',')
				j++;
			arr[i].color = ft_atoi_base(&line_splitted[i][j + 1],
					"0123456789abcdef");
		}
		else
			arr[i].color = 0x00ff00;
		free(line_splitted[i]);
	}
	free(line_splitted);
}

int	get_map_data(char *filename, t_gl *data_ptr)
{
	int		fd;
	char	*tmp;

	data_ptr->height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		(*data_ptr).height++;
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	if (get_map_width(fd, data_ptr) || check_valid(data_ptr))
		return (1);
	return (0);
}

int	file_check(char	*file, int fd, t_gl *data_ptr)
{
	int		i;
	char	*line;

	if (fd < 0)
		return (perror("open"), 1);
	if (get_map_data(file, data_ptr))
		return (1);
	data_ptr->width = data_ptr->map_width[1].width;
	(*data_ptr).map = malloc((*data_ptr).height * sizeof(t_map *));
	if (!(*data_ptr).map)
		return (write(2, "error: malloc failure!", 22), 1);
	i = -1;
	while (++i < (*data_ptr).height)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		(*data_ptr).map[i] = malloc((*data_ptr).width * sizeof(t_map));
		if (!(*data_ptr).map)
			return (write(2, "error: malloc failure!", 22), 1);
		fill_matrix(line, (*data_ptr).map[i], data_ptr);
		free(line);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:46:28 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/03 11:46:29 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static int	get_mapwidth(int fd, t_gl *gl_ptr)
{
	int		width;
	int		prev_width;
	int		i;
	char	*line;

	prev_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (prev_width && gl_ptr->width != prev_width)
			return (0);
		prev_width = gl_ptr->width;
		width = 0;
		i = -1;
		while (line[++i])
		{
			if ((line[i] != ' ' && line[i] != '\n') && (line[i + 1] == '\n'
					|| line[i + 1] == ' ' || line[i + 1] == '\0'))
				width++;
		}
		gl_ptr->width = width;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

static void	init_matrix_points(char *line, int x, t_map *arr, t_gl *data)
{
	int	j;

	arr[x].x = x;
	arr[x].z = ft_atoi(line);
	if (ft_strchr(line, ','))
	{
		data->colored = 1;
		j = 0;
		while (line[j] && line[j] != ',')
			j++;
		arr[x].color = mini_atoi_base(&line[j + 1]);
	}
	else
		arr[x].color = BASE_COLOR;
}

static void	fill_matrix(char *line, int y, t_map *arr, t_gl *data_ptr)
{
	int		x;
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return ;
	x = -1;
	while (++x < (*data_ptr).width)
	{
		arr[x].y = y;
		init_matrix_points(line_splitted[x], x, arr, data_ptr);
		data_ptr->z_min = arr[x].z;
		z_height_definition(arr[x].z, data_ptr);
		free(line_splitted[x]);
	}
	free(line_splitted);
}

static int	get_mapdata(char *filename, t_gl *data_ptr)
{
	int		fd;
	char	*tmp;

	data_ptr->height = 0;
	data_ptr->width = 0;
	data_ptr->z_max = 0;
	data_ptr->z_min = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
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
		return (perror("open"), 0);
	if (!get_mapwidth(fd, data_ptr) || !data_ptr->width)
		return (write(2, "error: invalid map!", 19), 0);
	return (1);
}

void	map_init(char	*file, t_gl *data)
{
	int		i;
	int		fd;
	char	*line;

	data->colored = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(0));
	if (!get_mapdata(file, data))
		exit(0);
	(*data).map = malloc((*data).height * sizeof(t_map *));
	if (!(*data).map)
		return (perror("malloc failure"), exit(0));
	i = -1;
	while (++i < (*data).height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*data).map[i] = malloc((*data).width * sizeof(t_map));
		if (!(*data).map)
			return (perror("malloc failure"), clear_map(data, i), exit(0));
		fill_matrix(line, i, (*data).map[i], data);
		free(line);
	}
}

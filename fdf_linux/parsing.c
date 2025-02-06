/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:11:29 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/05 22:11:30 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void	init_matrix_points(char *line, int x, t_map *arr, t_gl *data)
{
	int	j;

	arr[x].x = x;
	arr[x].z = ft_atoi(line);
	if (arr[x].z > SIZE_Y)
		arr[x].z = SIZE_Y;
	else if (arr[x].z < -SIZE_Y)
		arr[x].z = -SIZE_Y;
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

static int	fill_matrix(char *line, int y, t_map *arr, t_gl *data_ptr)
{
	int		x;
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (perror("malloc failure"), 0);
	x = -1;
	while (++x < (*data_ptr).width)
	{
		arr[x].y = y;
		if (!(ft_isdigit(line_splitted[x][0])
			|| line_splitted[x][0] == '-' || line_splitted[x][0] == '+'))
			return (write(2, "error: invalid map!", 19),
				clear_double(line_splitted), 0);
		init_matrix_points(line_splitted[x], x, arr, data_ptr);
		data_ptr->z_min = arr[x].z;
		z_height_definition(arr[x].z, data_ptr);
	}
	clear_double(line_splitted);
	return (1);
}

static int	get_mapwidth(int fd, t_gl *gl_ptr)
{
	int		curr_width;
	int		prev_width;
	char	*line;

	prev_width = 0;
	line = get_next_line(fd, 1);
	while (line)
	{
		curr_width = words_counter(line);
		if (prev_width && curr_width != prev_width)
			return (free(line), get_next_line(fd, 0), 0);
		prev_width = curr_width;
		gl_ptr->width = curr_width;
		if (gl_ptr->width == 0)
			return (free(line), get_next_line(fd, 0), 0);
		free(line);
		line = get_next_line(fd, 1);
	}
	return (close(fd), 1);
}

static int	get_mapdata(char *filename, t_gl *data_ptr)
{
	int		fd;
	char	*tmp;

	data_ptr->height = 0;
	data_ptr->width = 0;
	data_ptr->z_max = 0;
	data_ptr->z_min = 0;
	data_ptr->colored = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	tmp = get_next_line(fd, 1);
	while (tmp)
	{
		(*data_ptr).height++;
		free(tmp);
		tmp = get_next_line(fd, 1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	if (!get_mapwidth(fd, data_ptr) || !data_ptr->width)
		return (write(2, "error: invalid map!", 19), 0);
	return (1);
}

void	map_init(char	*file, int fd, t_gl *data)
{
	int		i;
	char	*line;

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
		line = get_next_line(fd, 1);
		if (!line)
			break ;
		(*data).map[i] = malloc((*data).width * sizeof(t_map));
		if (!(*data).map)
			return (perror("malloc failure"), clear_map(data, i), exit(0));
		if (!fill_matrix(line, i, (*data).map[i], data))
			return (clear_map(data, ++i), free(line)
				, get_next_line(fd, 0), exit(0));
		free(line);
	}
	get_next_line(fd, 0);
}

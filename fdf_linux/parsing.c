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

void	max_min_set(int z, t_gl *gl_ptr)
{
	if (z > gl_ptr->z_high)
		gl_ptr->z_high = z;
	else if (z < gl_ptr->z_min)
		gl_ptr->z_min = z;
}

void	init_matrix_points(char *line, int x, t_map *arr, t_gl *data)
{
	int	j;

	arr[x].x = x;
	arr[x].z = ft_atoi(line);
	if (arr[x].z)
		arr[x].alt_switch = 1;
	if (ft_strchr(line, ','))
	{
		data->colored = 1;
		j = 0;
		while (line[j] && line[j] != ',')
			j++;
		arr[x].color = mini_atoi_base(&line[j + 1]);
	}
	else
	{
		if (arr[x].z > 0)
			arr[x].color = data->mc.high_altitude_color;
		else if (arr[x].z == 0)
			arr[x].color = data->mc.base_color;
		else
			arr[x].color = data->mc.low_altitude_color;
	}
}

static void	fill_matrix(char *line, int y, t_map *arr, t_gl *data_ptr)
{
	int		x;
	char	**line_splitted;

	data_ptr->mc.base_color = 0xf302b63;
	data_ptr->mc.high_altitude_color = 0xADA996;
	data_ptr->mc.low_altitude_color = 0x00ff00;
	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return ;
	x = -1;
	while (++x < (*data_ptr).width)
	{
		arr[x].y = y;
		init_matrix_points(line_splitted[x], x, arr, data_ptr);
		data_ptr->z_min = arr[x].z;
		max_min_set(arr[x].z, data_ptr);
		free(line_splitted[x]);
	}
	free(line_splitted);
}

int	get_map_data(char *filename, t_gl *data_ptr)
{
	int		fd;
	char	*tmp;

	data_ptr->height = 0;
	data_ptr->width = 0;
	data_ptr->z_high = 0;
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
	if (!get_map_width(fd, data_ptr) || !data_ptr->width)
		return (write(2, "error: invalid map!", 19), 0);
	return (1);
}

void	file_check(char	*file, t_gl *data)
{
	int		i;
	int		fd;
	char	*line;

	data->colored = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(0));
	if (!get_map_data(file, data))
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
			return (perror("malloc failure"),exit(0));
		fill_matrix(line, i, (*data).map[i], data);
		free(line);
	}
}

// int main(int argc, char **argv)
// {
// 	t_gl	gl;

// 	if (argc < 1)
// 		return (printf("invalid args"), 0);
// 	file_check(argv[1], &gl);
// 	// printf("%d >> %d\nz_min: %d z_max%d\n", gl.width, gl.height, gl.z_min, gl.z_high);
// 	for (int i = 0; i < gl.height; i++)
// 	{
// 		for (int j = 0; j < gl.width; j++)
// 			printf("%d, %d ", gl.map[i][j].z, gl.map[i][j].color);
// 		printf("\n");
// 	}
// 	return (0);
// }
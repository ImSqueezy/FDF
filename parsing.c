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
			return (write(1, "error: srrrrlid map!", 19), 1);
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
	return (close(fd), 0);
}

void	fill_points(char *line, int x, t_map *arr)
{
	int	j;

	arr[x].x = x;
	arr[x].z = ft_atoi(line);
	if (ft_strchr(line, ','))
	{
		j = 0;
		while (line[j] && line[j] != ',')
			j++;
		arr[x].color = ft_atoi_base(&line[j + 1],
				"0123456789abcdef");
	}
	else
		arr[x].color = 0xffffff;
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
		fill_points(line_splitted[x], x, arr);
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
	if (get_map_width(fd, data_ptr))
		return (1);
	return (0);
}

int	file_check(char	*file, int fd, t_gl *data_ptr)
{
	int		i;
	char	*line;

	if (get_map_data(file, data_ptr))
		return (1);
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
		fill_matrix(line, i, (*data_ptr).map[i], data_ptr);
		free(line);
	}
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_gl	gl;
// 	int		fd;

// 	if (argc < 1)
// 		return (printf("invalid args"), 0);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (perror("open"), 0);
// 	if (file_check(argv[1], fd, &gl))
// 		printf("invalid\n");
// 	// for (int i = 0; i < gl.height; i++)
// 	// {
// 	// 	for (int j = 0; j < gl.width; j++)
// 	// 		printf("%d", gl.map[i][j].z);
// 	// 	printf("\n");
// 	// // }
// 	urn (0);
// }
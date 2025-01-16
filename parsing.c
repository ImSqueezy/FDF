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

static void get_map_data(char *filename, t_gl *data_ptr)
{
	int		i;
	int		fd;
	char	*tmp;

	data_ptr->width = 0;
	data_ptr->height = 0;
	fd = open(filename, O_RDONLY);
	tmp = get_next_line(fd);
	i = 0;
	while (tmp[i])
	{
		if ((tmp[i] != 32 && tmp[i + 1] == 32) || tmp[i + 1] == '\0')
			(*data_ptr).width++;
		i++;
	}
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		(*data_ptr).height++;
	}
	close(fd);
}

void	z_color_definition(int z, int *color)
{
	if (z == 0)
		*color = 0xFFFFFF;
	if (z != 0)
		*color = 0xFF0000;
}

static void	fill_matrix(char *line, t_map *arr, t_gl *data_ptr)
{
	int		i;
	int		j;
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return ;
	i = 0;
	while (i < (*data_ptr).width)
	{
		arr[i].z = ft_atoi(line_splitted[i]);
		if (ft_strchr(line_splitted[i], ','))
		{
			j = 0;
			while (line_splitted[i][j] && line_splitted[i][j] != ',')
				j++;
			arr[i].color = ft_atoi_base(&line_splitted[i][j + 1],
					"0123456789ABCDEF");
		}
		z_color_definition(arr[i].z, &arr[i].color);
		free(line_splitted[i]);
		i++;
	}
	free(line_splitted);
}

void	file_check(char	*file, t_gl *data_ptr)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	get_map_data(file, data_ptr);
	(*data_ptr).map = malloc((*data_ptr).height * sizeof(t_map *));
	if (!(*data_ptr).map)
		write(2, "MALLOC FAILURE", 14);
	i = 0;
	while (i < (*data_ptr).height)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		(*data_ptr).map[i] = malloc((*data_ptr).width * sizeof(t_map));
		if (!(*data_ptr).map)
			write(2, "MALLOC FAILURE", 14);
		fill_matrix(line, (*data_ptr).map[i], data_ptr);
		i++;
		free(line);
	}
}

// int main(int argc, char **argv)
// {
// 	t_gl gl_v;
// 	if (argc != 2)
// 		printf("nbr of args isn't correct!");
// 	file_check(argv[1], &gl_v);
// 	// printf("%3d,%d", gl_v.map[0][0].z, gl_v.map[0][0].color);
// 	// int j;
// 	// int i = 0;
// 	// while (i < gl_v.height)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < gl_v.width)
// 	// 	{
// 	// 		// printf("%3d,%d", gl_v.map[i][j].z, gl_v.map[i][j].color);
// 	// 		printf("[%3d][%d],", i,j);
// 	// 		j++;
// 	// 	}
// 	// 	printf("\n");
// 	// 	i++;
// 	// }
// 	return (0);
// }
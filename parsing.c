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

static void	get_map_data(char *filename, t_gl *data_ptr)
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
		else
			arr[i].color = 0x00ff00;
		free(line_splitted[i]);
		i++;
	}
	free(line_splitted);
}

int	file_check(char	*file, t_gl *data_ptr)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	get_map_data(file, data_ptr);
	(*data_ptr).map = malloc((*data_ptr).height * sizeof(t_map *));
	if (!(*data_ptr).map)
		return (write(2, "error: malloc failure!", 22), 0);
	i = 0;
	while (i < (*data_ptr).height)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		(*data_ptr).map[i] = malloc((*data_ptr).width * sizeof(t_map));
		if (!(*data_ptr).map)
			return (write(2, "error: malloc failure!", 22), 0);
		fill_matrix(line, (*data_ptr).map[i], data_ptr);
		i++;
		free(line);
	}
	return (1);
}

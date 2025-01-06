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

void	get_map_data(char *filename, g_data *data_ptr)
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

void	fill_array(char *line, int **arr, g_data *data_ptr)
{
	static unsigned int		i;
	unsigned int			j;
	char					**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return ;
	j = 0;
	while (j < (*data_ptr).width)
	{
		arr[i][j] = ft_atoi(line_splitted[j]);
		free(line_splitted[j]);
		j++;
	}
	free(line_splitted);
	i++;
}

void	file_check(char	*file, g_data *data_ptr)
{
	unsigned int		i;
	int					fd;
	char				*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	get_map_data(file, data_ptr);
	(*data_ptr).array = malloc((*data_ptr).height * sizeof(int *));
	if (!(*data_ptr).array)
		write(2, "MALLOC FAILURE", 14);
	i = 0;
	while (i < (*data_ptr).height)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		(*data_ptr).array[i] = malloc((*data_ptr).width * sizeof(int));
		if (!(*data_ptr).array)
			write(2, "MALLOC FAILURE", 14);
		fill_array(line, (*data_ptr).array, data_ptr);
		i++;
		free(line);
	}
}

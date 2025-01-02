#include "FDF.h"

typedef struct data_struct
{
	unsigned int	width;
	unsigned int	height;
	int				**array;
} d_st;

void	get_map_data(char *filename, d_st **data_ptr)
{
	int		i;
	int		fd;
	char	*tmp;
	
	fd = open(filename, O_RDONLY);
	tmp = get_next_line(fd);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != 32 && tmp[i + 1] == 32 || tmp[i + 1] == '\0')
		(*data_ptr)->width++;
		i++;
	}
	while (tmp)
	{
	 	free(tmp);
		tmp = get_next_line(fd);
	 	(*data_ptr)->height++;
	}
	close(fd);
}

void	fill_array(char *line, int **arr, d_st **data_ptr)
{
	int		i;
	int		j;
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	i = 0;
	while (i < (*data_ptr)->height && line[i])
	{
		arr[i] = malloc(sizeof(int) * (*data_ptr)->width);
		if (!arr[i])
		{
			write(2, "Memory allocation failed\n", 25);
			return ;
		}
		j = 0;
		while (j < (*data_ptr)->width)
		{
			arr[i][j] = ft_atoi(line_splitted[i]);
			j++;
		}
		free(line_splitted[i]);
		i++;
	}
	free(line_splitted);
}

void	file_check(char	*file, d_st **data_ptr)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	get_map_data(file, data_ptr);
	(*(*data_ptr)).array = (int **)malloc((*data_ptr)->height * sizeof(int *));
	i = 0;
	while (i < (*data_ptr)->height)
	{
		line = get_next_line(fd);
		(*(*data_ptr)).array[i] = (int *)malloc((*data_ptr)->width * sizeof(int *));
		if (!(*data_ptr)->array)
			write(2, "MALLOC ERROR", 12);
		fill_array(line, &(*data_ptr)->array[i], data_ptr);
		i++;
		free(line);
	}
}

int main(int argc, char **argv)
{
	d_st	*data_ptr;

	if (argc != 2)
		return (write(2, "Invalid number of arguments!", 28), 0);
	(data_ptr) = malloc(sizeof(d_st));
	(data_ptr)->width = 0;
	(data_ptr)->height = 0;
	file_check(argv[1], &data_ptr);
	system("leaks a.out");
	return (0);
}

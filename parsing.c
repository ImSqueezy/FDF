#include "FDF.h"

typedef struct data_struct
{
	unsigned int	width;
	unsigned int	height;
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

// open the file
// handle errors in get_next_line (done)
// read from it and store in tmp pointer (free each assign)
void	file_check(char	*file, d_st **data_ptr)
{
	int		fd;
	char	*tmp;

	fd = open(file, O_RDONLY);
	init_map_data(file, &data_ptr);
	tmp = "";
	while (tmp)
	{
		tmp = get_next_line(fd);
		free(tmp);
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
	return (0);
}
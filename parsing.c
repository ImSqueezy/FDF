#include "FDF.h"

typedef struct data_struct
{
	unsigned int	width;
	unsigned int	height;
	void			*mlx_ptr;
	void			*win_ptr;
	int				**array;
	t_img			img;
} d_st;

typedef	struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

void	get_map_data(char *filename, d_st *data_ptr)
{
	int		i;
	int		fd;
	char	*tmp;
	
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

void	fill_array(char *line, int **arr, d_st *data_ptr)
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
	ree(line_splitted);
	i++;
}

void	img_pix_put(t_img *img, int x, inty , int color)
{
	char *pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / *));
	*(int *)pixel = color;
}

void	file_check(char	*file, d_st *data_ptr)
{
	unsigned int		i;
	int					fd;
	char				*line;

	fd = open(file, O_RDONLY);
	get_map_data(file, data_ptr);
	(*data_ptr).array = malloc((*data_ptr).height * sizeof(int *));
	i = 0;
	while (i < (*data_ptr).height)
	{
		line = get_next_line(fd);
		(*data_ptr).array[i] = malloc((*data_ptr).width * sizeof(int));
		if (!(*data_ptr).array)
			write(2, "MALLOC ERROR", 12);
		fill_array(line, (*data_ptr).array, data_ptr);
		i++;
		free(line);
	}
}

int	draw_pixel(d_st *data_ptr)
{
	data_ptr->img.mlx_img = mlx_new_image(data_ptr, SIZE_X, SIZE_Y);
	return (0);
}

void	connection_init(char *map, d_st *data_ptr)
{
	char	*title;
	
	title = ft_strjoin("aouaalla's FDF : ", map);
	(*data_ptr).width = 0;
	(*data_ptr).height = 0;
	(*data_ptr).mlx_ptr = mlx_init();
	(*data_ptr).win_ptr = mlx_new_window((*data_ptr).mlx_ptr, SIZE_X, SIZE_Y, title);

}

int main(int argc, char **argv)
{
	d_st	data_ptr;

	if (argc != 2)
		return (write(2, "Invalid number of arguments!", 28), 0);
	connection_init(argv[1], &data_ptr);
	file_check(argv[1], &data_ptr);
	// draw_pixel(&data_ptr);
	mlx_loop_hook(data_ptr.mlx_ptr, &draw_pixel, &data_ptr);
	mlx_loop(data_ptr.mlx_ptr);
	//system("leaks a.out");
	return (0);
}

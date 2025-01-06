#ifndef FDF_H
# define FDF_H

# define SIZE_X 600
# define SIZE_Y 300

# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct image_data
{
	void	*mlx_img;
	char	*addr;
	int		bp_pixel;
	int		line_len;
	int		endian;
}	i_data;

typedef struct global_data
{
	unsigned int	width;
	unsigned int	height;
	void			*mlx_ptr;
	void			*win_ptr;
	int				**array;
}	g_data;

typedef struct s_rect // testing
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;

void	connection_init(char *map, g_data *data_ptr, i_data *img_ptr);
void	file_check(char	*file, g_data *data_ptr);
void	fill_array(char *line, int **arr, g_data *data_ptr);
void	get_map_data(char *filename, g_data *data_ptr);
int		draw_onWin(g_data *gl_ptr, i_data *im_ptr);

#endif


#include <stdlib.h>
#include <stdio.h>

#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

#define SIZE_X 400
#define SIZE_Y 300

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000

typedef struct s_image
{
	void	*win;
	char	*addr;
	int		line_len;
	int		bp_pixel;
	int		endian;
}	t_img;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
	t_img	img;
}	t_data;

void	pixel_put(t_data *gl_ptr, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pxl = gl_ptr->img.addr + (y * gl_ptr->img.line_len
				+ x * (gl_ptr->img.bp_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}


int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    return (0);
}

int	render(t_data *data)
{
    /* if window has been destroyed, we don't want to put the pixel ! */
    if (!data->win_ptr)
		return (1);
	int i = 0;
	int j;
	 j = 0;
	while (i < SIZE_X) {
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,j, i, 0xffffff);
			j++;
		i++;
	}
    return (0);
}

int	main(void)
{
    t_data	data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, SIZE_X, SIZE_Y,
                                "my window");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (MLX_ERROR);
    }
	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	return (0);
}
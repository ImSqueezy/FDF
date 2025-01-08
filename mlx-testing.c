#include "FDF.h"

int	pixel_put(i_data *img_ptr, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pixel = img_ptr->addr + (y * img_ptr->line_len + x * (img_ptr->bp_pixel / 8));
    	*(int *)pixel = color;
	}
}

int main()
{
	g_data gl;
	i_data img;

	gl.mlx_ptr = mlx_init();
	gl.win_ptr = mlx_new_window(gl.mlx_ptr, SIZE_X, SIZE_Y, "this is a title");
	img.mlx_img = mlx_new_image(gl.mlx_ptr, SIZE_X, SIZE_Y);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bp_pixel, &img.line_len, &img.endian);
	int j;
	int i = 0;
	while (i < SIZE_X)
	{
		j = 0;
		while (j < SIZE_Y)
		{
			pixel_put(img.mlx_img, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_loop(gl.mlx_ptr);
	return (0);
}
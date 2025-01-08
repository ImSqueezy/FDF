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


int handle_nothing(void)
{
	return (0);
}

int	key_handle(int keysysm, g_data *gl_ptr)
{
	if (keysysm == XK_Escape)
	{
		mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
		printf("BYE!");
	}
	return (0);
}

int main()
{
	g_data gl;
	i_data img;

	gl.mlx_ptr = mlx_init();
	gl.win_ptr = mlx_new_window(gl.mlx_ptr, SIZE_X, SIZE_Y, "this is a title");
	img.mlx_img = mlx_new_image(gl.mlx_ptr, SIZE_X, SIZE_Y);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bp_pixel, &img.line_len, &img.endian);

	// mlx_loop_hook(gl.mlx_ptr, &handle_nothing, &gl);
	// mlx_hook(gl.win_ptr, KeyPress, KeyPressMask, &key_handle, &gl);

	 //printf("%d %d %p\n", img.bp_pixel, img.line_len, img.addr);
	int j;
	int i = 0;
	while (i < SIZE_X)
	{
		j = 0;
		while (j < SIZE_Y)
		{
			//mlx_pixel_put(gl.mlx_ptr, gl.win_ptr, SIZE_X, SIZE_Y, 0xFFFFFF);
			//pixel_put(&img, i, j, 0xFFFFFF);
			*((int *)(img.addr + (j * img.line_len + i * (img.bp_pixel / 8)))) = 0x00FF00;
			j++;
		}
		i++;
	}

	mlx_loop(gl.mlx_ptr);
	// mlx_destroy_display(gl.mlx_ptr); // is it necessary! the behavior is fine without it.
	return (0);
}
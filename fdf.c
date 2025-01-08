/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:08:26 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/06 16:08:27 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int	connection_init(char *map, g_data *data_ptr, i_data *img_ptr)
{
	char	*title;

	// title = ft_strjoin("aouaalla's FDF : ", map);
	title = map;
	data_ptr->mlx_ptr = mlx_init();
	if (!data_ptr->mlx_ptr)
		return (0);
	data_ptr->win_ptr = mlx_new_window(data_ptr->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!img_ptr->mlx_img)
		return (0);
	img_ptr->mlx_img = mlx_new_image(data_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!img_ptr->mlx_img)
		return (0);
	img_ptr->addr = mlx_get_data_addr(img_ptr->mlx_img, &img_ptr->bp_pixel,
			&img_ptr->line_len, &img_ptr->endian);
	if (!img_ptr->addr)
		return (0);
	return (0);
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

void pixel_put(g_data *gl_ptr, int x, int y, int color)
{
    char *pxl;
    
    if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
    {
        pxl = gl_ptr->img.addr + (y * gl_ptr->img.line_len + x * (gl_ptr->img.bp_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

void ft_draw_line(g_data *gl_ptr, int x1, int y1, int x2, int y2, int color)
{
    int i;
    int step;
    int delta_x;
    int delta_y;
    
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    if (abs((int)delta_x) >= abs((int)delta_y))
        step = abs((int)delta_x);
    else
        step = abs((int)delta_y);
    delta_x /= step;
    delta_y /= step;
    i = 0;
    while (i < step)
    {
        pixel_put(gl_ptr, x1, y1, color);
        x1 += delta_x;
        y1 += delta_y;
        i++;
    }
}

int main(int argc, char **argv)
{
	g_data	gl;
	i_data	im;

	if (argc < 1)
		return (write(2, "Invalid number of arguments!", 28), 0);
	// file_check(argv[1], &gl);
	connection_init(argv[1], &gl, &im);
	ft_draw_line(&gl, 0, 0, SIZE_X, SIZE_Y, 0xFFFFFF);
	mlx_loop_hook(gl.mlx_ptr, &handle_nothing, &gl);
	mlx_hook(gl.win_ptr, KeyPress, KeyPressMask, &key_handle, &gl);
	mlx_loop(gl.mlx_ptr);
	mlx_destroy_display(gl.mlx_ptr); // is it necessary! the behavior is fine without it.
	system("leaks a.out");
	return (0);
}

// minilibx uses an extension which allows our program
// to share images with the Xwindow server through shared
// memory (/dev/shm)

// mlx_get_data_addr returns the address of the images
// as a simple array of pixels (char *)


// with images instead of mlx_pixel_put, we will be able to
// change the pixels directly using a pointer
// (way faster)

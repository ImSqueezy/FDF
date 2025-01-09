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


int	connection_init(char *map, g_data *data_ptr)
{
	char	*title;

	title = ft_strjoin("aouaalla's FDF : ", map);
	data_ptr->mlx_ptr = mlx_init();
	if (!data_ptr->mlx_ptr)
		return (0);
	data_ptr->win_ptr = mlx_new_window(data_ptr->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!data_ptr->win_ptr)
		return (0);
	data_ptr->img.mlx_img = mlx_new_image(data_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!data_ptr->img.mlx_img)
		return (0);
	data_ptr->img.addr = mlx_get_data_addr(data_ptr->img.mlx_img, &data_ptr->img.bp_pixel,
			&data_ptr->img.line_len, &data_ptr->img.endian);
	if (!data_ptr->img.addr)
		return (0);
	data_ptr->zoom = 18;	
	return (0);
}

int	key_handle(int keysysm, g_data *gl_ptr)
{
	if (keysysm == XK_Escape)
	{
		mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
		gl_ptr->win_ptr = NULL;
		printf("WINDOW CLOSED!");
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

void	line_draw(float x, float y, float x1, float y1, g_data *gl_ptr)
{
	float	dx;
	float	dy;
	float	step;

	dx = x1 -x;
	dy = y1 - y;
	if (abs((int)dx) > ((int)dy))
		step = abs((int)dx);
	else
		step = abs((int)dy);
	dx /= step;
	dy /= step;
	while ((int)step)
	{
		pixel_put(gl_ptr, (x + SIZE_X/2) - (gl_ptr->width * gl_ptr->zoom)/2, (y + SIZE_Y/2) - (gl_ptr->height * gl_ptr->zoom)/2, 0xFFFFFF);
		x += dx;
		y += dy;
		--step;
	}
}


int	draw(g_data *gl_ptr)
{
	int	i;
	int	j;

	if (!gl_ptr->win_ptr)
		return (0);
	i = 0;
	while (i < gl_ptr->height)
	{
		j = 0;
		while (j < gl_ptr->width)
		{
			if (j != gl_ptr->width - 1)	
				line_draw(j * gl_ptr->zoom, i * gl_ptr->zoom, (j + 1) * gl_ptr->zoom, i * gl_ptr->zoom, gl_ptr);
			if (i != gl_ptr->height -1)
				line_draw(j* gl_ptr->zoom, i* gl_ptr->zoom, j * gl_ptr->zoom, (i + 1) * gl_ptr->zoom, gl_ptr);	
			j++;
		}
		i++;
	}
	// pixel_put(gl_ptr, SIZE_X/2, SIZE_Y/2, 0xFFFFFF);
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr, gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

void	hooks(g_data *gl_ptr)
{
	mlx_hook(gl_ptr->win_ptr, KeyPress, KeyPressMask, &key_handle, gl_ptr);

}

int main(int argc, char **argv)
{
	g_data	gl;

	if (argc < 1)
		return (write(2, "Invalid number of arguments!", 28), 0);
	file_check(argv[1], &gl);
	connection_init(argv[1], &gl);

	mlx_loop_hook(gl.mlx_ptr, &draw, &gl);
	hooks(&gl);

	mlx_loop(gl.mlx_ptr);
	mlx_destroy_image(gl.mlx_ptr, gl.img.mlx_img);
    mlx_destroy_display(gl.mlx_ptr);
	system("leaks a.out");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:56:22 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/06 15:56:24 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int	connection_init(char *map, g_data *data_ptr, i_data *img_ptr)
{
	char	*title;

	title = ft_strjoin("aouaalla's FDF : ", map);
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

int	handle_nothing(void)
{
	return (0);
}

int	key(int keysysm, g_data *gl_ptr)
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

int	draw_onWin(g_data *gl_ptr, i_data *im_ptr)
{
	if (gl_ptr->win_ptr == NULL)
        return (1);

	(void)im_ptr;
	// ft_draw_line(gl_ptr, 10, 10, SIZE_X, SIZE_Y, 0xFFFFFF);

	mlx_loop_hook(gl_ptr->mlx_ptr, &handle_nothing, gl_ptr);
	mlx_hook((*gl_ptr).win_ptr, KeyPress, KeyPressMask, &key, gl_ptr);

	return (0);
}

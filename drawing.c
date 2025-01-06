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

void	connection_init(char *map, g_data *data_ptr, i_data *img_ptr)
{
	char	*title;

	title = ft_strjoin("aouaalla's FDF : ", map);
	data_ptr->mlx_ptr = mlx_init();
	data_ptr->win_ptr = mlx_new_window(data_ptr->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!img_ptr->mlx_img)
		return ;
	img_ptr->mlx_img = mlx_new_image(data_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!img_ptr->mlx_img)
		return ;
	img_ptr->addr = mlx_get_data_addr(img_ptr->mlx_img, &img_ptr->bp_pixel,
			&img_ptr->line_len, &img_ptr->endian);
	if (!img_ptr->addr)
		return ;
}

void	img_pix_put(i_data *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bp_pixel / 8));
    *(unsigned int *)pixel = color;
}

void	render_background(i_data *img, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < SIZE_Y)
    {
        j = 0;
        while (j < SIZE_X)
            img_pix_put(img, j++, i, color);
		i++;
    }
}

int	draw_onWin(g_data *gl_ptr, i_data *im_ptr)
{
	(void )	im_ptr;
	if (gl_ptr->win_ptr == NULL)
        return (1);
    render_background(im_ptr, 0xFFFFFF);
    mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr, (*im_ptr).mlx_img, 0, 0);
	mlx_loop(gl_ptr->mlx_ptr);
	return (0);
}

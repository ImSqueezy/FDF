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
		mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
	printf("BYE!");
	return (0);
}

int	draw_onWin(g_data *gl_ptr, i_data *im_ptr)
{
	if (gl_ptr->win_ptr == NULL)
        return (1);

	
    mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr, (*im_ptr).mlx_img, 0, 0);
	// setting up hooks
	mlx_loop_hook(gl_ptr->mlx_ptr, &handle_nothing, gl_ptr);
	mlx_hook((*gl_ptr).win_ptr, KeyPress, KeyPressMask, &key, gl_ptr);
	mlx_loop((*gl_ptr).mlx_ptr);
	mlx_destroy_display((*gl_ptr).mlx_ptr);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_connection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:35:46 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/03 12:35:48 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void	defaults(t_gl *data)
{
	data->zoom = (SIZE_X / data->width) / 3;
	if (data->zoom == 0)
		data->zoom = 0.52;
	data->iso = 1;
	data->bonus = 0;
	data->cam.z_alti = 1;
	data->cam.x_scale = 0;
	data->cam.y_scale = 0;
}

int	connection_init(char *map, t_gl *data)
{
	char	*tmp;

	tmp = ft_strchr(map, '/');
	data->title = ft_strjoin("aouaalla's FDF : ", ++tmp);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (connection_terminator(data), 0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SIZE_X, SIZE_Y, data->title);
	if (!data->win_ptr)
		return (connection_terminator(data), 0);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, SIZE_X, SIZE_Y);
	if (!data->img.mlx_img)
		return (connection_terminator(data), 0);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bp_pixel, &data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		return (connection_terminator(data), 0);
	defaults(data);
	return (1);
}

int	connection_terminator(t_gl *data)
{
	if (data->img.mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = NULL;
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	clear_map(data, data->height);
	free(data->title);
	return (1);
}

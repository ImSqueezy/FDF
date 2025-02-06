/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:18:26 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/03 16:18:27 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static int	zoom_in_out(int code, t_gl *data)
{
	if (code == XK_minus)
		data->zoom /= 1.24;
	if (data->zoom >= 1345.080933)
		return (0);
	if (code == XK_equal)
		data->zoom *= 1.24;
	return (0);
}

static void	transparent_base(int *color, t_gl *data)
{
	if (*color == BLACK && data->width < 100)
		*color = BASE_COLOR;
	else if (*color != BLACK && data->width < 100)
		*color = BLACK;
}

static void	change_altitude(int code, t_gl *data)
{
	int	i;
	int	j;

	if (code == XK_j)
		data->cam.z_alti -= 0.02;
	else if (code == XK_k)
		data->cam.z_alti += 0.02;
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (code == XK_n && data->map[i][j].z == data->z_min)
				transparent_base(&data->map[i][j].color, data);
		}
	}
}

static void	scaling(int code, t_gl *data)
{
	if (code == XK_h)
		data->cam.x_scale += 10;
	else if (code == XK_g)
		data->cam.x_scale -= 10;
	if (code == XK_v)
		data->cam.y_scale += 10;
	else if (code == XK_y)
		data->cam.y_scale -= 10;
}

int	keybr_hooks(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
		connection_terminator(gl_ptr);
	else if (keysysm == XK_minus || keysysm == XK_equal)
		zoom_in_out(keysysm, gl_ptr);
	else if (keysysm == XK_j || keysysm == XK_k || keysysm == XK_n)
		change_altitude(keysysm, gl_ptr);
	else if (keysysm == XK_t)
	{
		if (gl_ptr->iso == 1)
			gl_ptr->iso = 0;
		else
			gl_ptr->iso = 1;
	}
	else if (keysysm == XK_b)
		gl_ptr->bonus = 1;
	else if (keysysm == XK_y || keysysm == XK_v || keysysm == XK_g
		|| keysysm == XK_h)
		scaling(keysysm, gl_ptr);
	rotation_hooks(keysysm, gl_ptr);
	return (0);
}

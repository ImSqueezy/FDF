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
	if (code == 45)
		data->zoom /= 1.24;
	if (data->zoom >= 1345.080933)
		return (0);
	if (code == 61)
	{
		if (data->zoom == 0)
			data->zoom += 1.24;
		data->zoom *= 1.24;
	}
	return (0);
}

static void	transparent_base(int code, int *color, int *point, t_gl *data)
{
	if (*color == BLACK)
		*color = BASE_COLOR;
	else
		*color = BLACK;
}

static void	change_altitude(int code, t_gl *data)
{
	int	i;
	int	j;

	if (code == 106)
		data->cam.z_alti -= 0.04;
	else if (code == 107)
		data->cam.z_alti += 0.04;
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (code == 110 && data->map[i][j].z == data->z_min)
				transparent_base(code, &data->map[i][j].color,
					&data->map[i][j].z, data);
		}
	}
}

static void	scaling(int code, t_gl *data)
{
	if (code == 104)
		data->cam.x_scale += 10;
	else if (code == 103)
		data->cam.x_scale -= 10;
	if (code == 118)
		data->cam.y_scale += 10;
	else if (code == 121)
		data->cam.y_scale -= 10;
}

int	keybr_hooks(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
		connection_terminator(gl_ptr);
	else if (keysysm == 61 || keysysm == 45)
		zoom_in_out(keysysm, gl_ptr);
	else if (keysysm == 106 || keysysm == 107 || keysysm == 110)
		change_altitude(keysysm, gl_ptr);
	else if (keysysm == 116)
	{
		if (gl_ptr->iso == 1)
			gl_ptr->iso = 0;
		else
			gl_ptr->iso = 1;
	}
	else if (keysysm == 98)
		gl_ptr->bonus = 1;
	else if (keysysm == 104 || keysysm == 121 || keysysm == 103
		|| keysysm == 118)
		scaling(keysysm, gl_ptr);
	return (0);
}

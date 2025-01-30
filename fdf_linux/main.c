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

void	connection_init(char *map, t_gl *gl_ptr)
{
	char	*title;

	title = ft_strjoin("aouaalla's FDF : ", map);
	gl_ptr->mlx_ptr = mlx_init();
	if (!gl_ptr->mlx_ptr)
		return ;
	gl_ptr->win_ptr = mlx_new_window(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!gl_ptr->win_ptr)
		return ; // the mlx_ptr must be freed
	gl_ptr->img.mlx_img = mlx_new_image(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!gl_ptr->img.mlx_img)
		return ; // the win_ptr must be freed alongside mlx_ptr
	gl_ptr->img.addr = mlx_get_data_addr(gl_ptr->img.mlx_img,
			&gl_ptr->img.bp_pixel, &gl_ptr->img.line_len, &gl_ptr->img.endian);
	if (!gl_ptr->img.addr)
		return ; // destroy display, window, and image
	gl_ptr->zoom = (SIZE_X / gl_ptr->width) / 3;
	if (gl_ptr->zoom == 0)
		gl_ptr->zoom = 0.52;	
	gl_ptr->iso = 1;
}

int program_exit(t_gl *gl_ptr)
{
	mlx_destroy_image(gl_ptr->mlx_ptr, gl_ptr->img.mlx_img);
	mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
	gl_ptr->img.addr == NULL;
	gl_ptr->win_ptr = NULL;
	gl_ptr->mlx_ptr = NULL;
	return (0);
}

int	zoom_in_out(int code, t_gl *data)
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

void z_manipulator(int *point, int *color, int code, t_gl *data)
{
	if (code == 107 && *point != 0)
	{
		if (*point != -1 && *point != 0)
			*point += 1;
		else
			*point += 2;
	}
	else if (code == 106 && *point != 0)
	{
		if (*point != 1)
			*point -= 1;
		else
			*point -= 2;
	}
	if (data->colored == 0)
	{
		if (*point < 0)
			*color = data->mc.low_altitude_color;
		else if (*point >= 0)
			*color = data->mc.high_altitude_color;
	}
}

void	change_altitude(int code, t_gl *data)
{
	int i;
	int	j;
	static int	color;

	color = data->mc.base_color;
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if ((code == 106 || code == 107) && data->map[i][j].z != 0/*data->map[i][j].z != 0*/)
			{
				printf("%d\n", data->map[i][j].z);
				z_manipulator(&data->map[i][j].z, &data->map[i][j].color, code, data);
			}
			else if (code == 110 && data->map[i][j].z == 0)
			{
				if (data->map[i][j].color == BLACK)
					data->map[i][j].color = color;
				else
					data->map[i][j].color = BLACK;
			}
		}
	}
}

int	key_handle(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
		program_exit(gl_ptr);
	if (keysysm == 61 || keysysm == 45) // does the zooming looks gay!
		zoom_in_out(keysysm, gl_ptr);
	if (keysysm == 107 || keysysm == 106 || 110) // bug needs to be fixed:
									// the big map julia altitude changing translates the whole graph
									// even the point that has the altitude of 0
									// edit: the bug appears to be when the map has no 0 base altitude
									// the minimum point starts from another value, julia from 1 as an example
		change_altitude(keysysm, gl_ptr);
	if (keysysm == 116)
	{
		if (gl_ptr->iso == 1)
			gl_ptr->iso = 0;
		else
			gl_ptr->iso = 1;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_gl	gl;

	if (argc < 1)
		return (printf("args!"), 0);
	file_check(argv[1], &gl);
	connection_init(argv[1], &gl);
	mlx_loop_hook(gl.mlx_ptr, draw, &gl);
	mlx_hook(gl.win_ptr, 17, 0, &program_exit, &gl);
	mlx_hook(gl.win_ptr, KeyPress, KeyPressMask, &key_handle, &gl);
	mlx_loop(gl.mlx_ptr);
	// free the map
	return (0);
}
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

void	init_matrices(t_gl *data)
{
	data->mat = malloc(3 * sizeof(t_mat));
	if (!data->mat)
		exit(0);

}

void	connection_init(char *map, t_gl *gl_ptr) // make errors for allocation failure
{
	char *tmp;

	tmp = ft_strchr(map, '/');
	gl_ptr->title = ft_strjoin("aouaalla's FDF : ", ++tmp);
	gl_ptr->mlx_ptr = mlx_init();
	if (!gl_ptr->mlx_ptr)
		return ;
	gl_ptr->win_ptr = mlx_new_window(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y, gl_ptr->title);
	if (!gl_ptr->win_ptr)
		return ;
	gl_ptr->img.mlx_img = mlx_new_image(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!gl_ptr->img.mlx_img)
		return ;
	gl_ptr->img.addr = mlx_get_data_addr(gl_ptr->img.mlx_img,
			&gl_ptr->img.bp_pixel, &gl_ptr->img.line_len, &gl_ptr->img.endian);
	if (!gl_ptr->img.addr)
		return ;
	gl_ptr->zoom = (SIZE_X / gl_ptr->width) / 3;
	if (gl_ptr->zoom == 0)
		gl_ptr->zoom = 0.52;
	gl_ptr->iso = 1;
	gl_ptr->bonus = 0;
	gl_ptr->cam.z_alti = 1;
	gl_ptr->cam.x_scale = 0;
	gl_ptr->cam.y_scale = 0;
}

int program_exit(t_gl *gl_ptr)
{
	int	i;

	mlx_destroy_image(gl_ptr->mlx_ptr, gl_ptr->img.mlx_img);
	mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
	gl_ptr->img.addr == NULL;
	gl_ptr->win_ptr = NULL;
	i = -1;
	while (++i < gl_ptr->height)
		free(gl_ptr->map[i]);
	free(gl_ptr->map);
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

void z_manipulator(t_map *p, int code, t_gl *data)
{
	if (code == 107 && p->alt_switch)
		p->z = p->z << 1;
	if (code == 106 && p->alt_switch)
		p->z = p->z >> 1;
	if (!data->colored)
	{
		if (p->z < 0)
			p->color = data->mc.low_altitude_color;
		else if (p->z > 0)
			p->color = data->mc.high_altitude_color;
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
			if ((code == 106 || code == 107))
				z_manipulator(&data->map[i][j], code, data);
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

void scaling(int code, t_gl *data)
{
	if (code == 104)
		data->cam.x_scale += 2;
	else if (code == 103)
		data->cam.x_scale -= 2;
	if (code == 118)
		data->cam.y_scale += 2;
	else if (code == 121)
		data->cam.y_scale -= 2;
}

int	key_handle(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
		program_exit(gl_ptr);
	if (keysysm == 61 || keysysm == 45)
		zoom_in_out(keysysm, gl_ptr);
	if (keysysm == 106 || keysysm == 107 || keysysm == 110)
		change_altitude(keysysm, gl_ptr);
	if (keysysm == 116)
	{
		if (gl_ptr->iso == 1)
			gl_ptr->iso = 0;
		else
			gl_ptr->iso = 1;
	}
	if (keysysm == 98)
		gl_ptr->bonus = 1;
	if (keysysm == 104 || keysysm == 121 || keysysm == 103 || keysysm == 118)
		scaling(keysysm, gl_ptr);
	printf("%d\n", keysysm);
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
	mlx_destroy_display(gl.mlx_ptr);
	free(gl.mlx_ptr);
	free(gl.title);
	return (0);
}

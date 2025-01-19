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

int	connection_init(char *map, t_gl *data_ptr)
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
	if (SIZE_X / data_ptr->width/2 > SIZE_Y / data_ptr->height/2)
		data_ptr->zoom = SIZE_X / data_ptr->width/2;
	else
		data_ptr->zoom = SIZE_Y / data_ptr->height/2;
	return (0);
}


int	draw(t_gl *gl_ptr)
{
	int	i;
	int	j;

	if (!gl_ptr->win_ptr)
		return (0);
	i = -1;
	while (++i < gl_ptr->height)
	{
		j = -1;
		while (++j < gl_ptr->width)
		{
			if (j != gl_ptr->width - 1)
				line_draw((t_coor){j, i, (j + 1), i, gl_ptr->map[i][j].color},
				gl_ptr);
			if (i != gl_ptr->height - 1)
				line_draw((t_coor){j, i, j, (i + 1), gl_ptr->map[i][j].color},
				gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

int	key_handle(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
	{
		mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
		gl_ptr->win_ptr = NULL;
		printf("WINDOW CLOSED!");
	}
	// printf("%d\n", keysysm);
	return (0);
}

void	hooks(t_gl *gl_ptr)
{
	mlx_hook(gl_ptr->win_ptr, KeyPress, KeyPressMask, &key_handle, gl_ptr);
}

int main(int argc, char **argv)
{
	t_gl	gl;

	if (argc < 1)
		return (write(2, "Invalid number of arguments!", 28), 0);
	if (!file_check(argv[1], &gl))
		return (0);
	connection_init(argv[1], &gl);
	draw(&gl);
	mlx_loop_hook(gl.mlx_ptr, &key_handle, &gl);
	hooks(&gl);
	mlx_loop(gl.mlx_ptr);
	mlx_destroy_image(gl.mlx_ptr, gl.img.mlx_img);
    mlx_destroy_display(gl.mlx_ptr);
	// system("leaks a.out");
	return (0);
}

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

int	connection_init(char *map, t_gl *gl_ptr)
{
	char	*title;

	title = ft_strjoin("aouaalla's FDF : ", map);
	gl_ptr->mlx_ptr = mlx_init();
	if (!gl_ptr->mlx_ptr)
		return (0);
	gl_ptr->win_ptr = mlx_new_window(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!gl_ptr->win_ptr)
		return (0);
	gl_ptr->img.mlx_img = mlx_new_image(gl_ptr->mlx_ptr, SIZE_X, SIZE_Y);
	if (!gl_ptr->img.mlx_img)
		return (0);
	gl_ptr->img.addr = mlx_get_data_addr(gl_ptr->img.mlx_img,
			&gl_ptr->img.bp_pixel, &gl_ptr->img.line_len, &gl_ptr->img.endian);
	if (!gl_ptr->img.addr)
		return (0);
	if (SIZE_X / gl_ptr->width/2 < SIZE_Y / gl_ptr->height/2)
	{
		gl_ptr->zoom = SIZE_X / gl_ptr->width/2;
		if (gl_ptr->zoom > 50)
			gl_ptr->zoom = 1;
	}
	else
		gl_ptr->zoom = SIZE_Y / gl_ptr->height/2;
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
	int		fd;
	t_gl	gl;

	if (argc != 2)
		return (write(2, "error: Invalid number of args", 28), 1);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	if (file_check(argv[1], fd, &gl))
		return (0);
	connection_init(argv[1], &gl);
	draw(&gl);
	mlx_loop_hook(gl.mlx_ptr, &key_handle, &gl);
	hooks(&gl);
	mlx_loop(gl.mlx_ptr);
	mlx_destroy_image(gl.mlx_ptr, gl.img.mlx_img);
    mlx_destroy_display(gl.mlx_ptr);
	return (0);
}

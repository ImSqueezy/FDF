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

int	main(int argc, char **argv)
{
	t_gl	gl;
	int		fd;

	if (argc != 2)
		return (write(2, "invalid number of args!", 23), 0);
	fd = open(argv[1], O_RDONLY);
	map_init(argv[1], fd, &gl);
	close (fd);
	if (!connection_init(argv[1], &gl))
		return (write(2, "connection initialization failed!", 33),
			close(fd), 1);
	mlx_loop_hook(gl.mlx_ptr, draw, &gl);
	mlx_hook(gl.win_ptr, DestroyNotify, 0, &connection_terminator, &gl);
	mlx_hook(gl.win_ptr, KeyPress, KeyPressMask, &keybr_hooks, &gl);
	mlx_loop(gl.mlx_ptr);
	mlx_destroy_display(gl.mlx_ptr);
	free(gl.mlx_ptr);
	return (0);
}

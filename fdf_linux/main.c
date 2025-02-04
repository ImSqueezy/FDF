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

	if (argc < 1)
		return (printf("args!"), 0);
	map_init(argv[1], &gl);
	if (!connection_init(argv[1], &gl))
		return (write(2, "connection initialization failed!", 33), 1);
	mlx_loop_hook(gl.mlx_ptr, draw, &gl);
	mlx_hook(gl.win_ptr, 17, 0, &connection_terminator, &gl);
	mlx_hook(gl.win_ptr, KeyPress, KeyPressMask, &keybr_hooks, &gl);
	mlx_loop(gl.mlx_ptr);
	mlx_destroy_display(gl.mlx_ptr);
	free(gl.mlx_ptr);
	return (0);
}

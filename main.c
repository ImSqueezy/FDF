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
	return (0);
}

// int main(int argc, char **argv)
// {
// 	int		fd;
// 	t_gl	gl;

// 	if (argc != 2)
// 		return (write(2, "error: Invalid number of args", 28), 1);
// 	if (!file_check(argv[1], &gl))
// 		return (0);
// 	// printf("here");
// 	// connection_init(argv[1], &gl);
// 	// hooks(&gl);
// 	// draw(&gl);
// 	// mlx_loop(gl.mlx_ptr);
//     // mlx_destroy_display(gl.mlx_ptr);
// 	return (0);
// }

int main(int argc, char **argv)
{
	t_gl	gl;

	if (argc != 2)
		return (printf("args!"), 0);
	int f = file_check(argv[1], &gl);
	// printf("%d", f);
	if (!file_check(argv[1], &gl))
		return (1);
	// printf("hello");
	// if (!file_check(argv[1], &gl));
	// 	return (0);
	// printf("txt");
	return (0);
}
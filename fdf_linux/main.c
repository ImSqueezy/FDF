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
	gl_ptr->iso = 1;
}

int program_exit(t_gl *gl_ptr)
{
	mlx_destroy_image(gl_ptr->mlx_ptr, gl_ptr->img.mlx_img);
	mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
	gl_ptr->win_ptr = NULL;
	return (0);
}

int	key_handle(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == 53)
		program_exit(gl_ptr);
	else
		printf("%d\n", keysysm);
	return (0);
}

int main(int argc, char **argv)
{
	t_gl	gl;

	if (argc != 2)
		return (printf("args!"), 0);
	file_check(argv[1], &gl);
	connection_init(argv[1], &gl);
	mlx_loop_hook(gl.mlx_ptr, draw, &gl);
	mlx_hook(gl.win_ptr, 17, 0, &program_exit, &gl);
	mlx_key_hook(gl.win_ptr, &key_handle, &gl);
	mlx_loop(gl.mlx_ptr);
	system("leaks a.out");
	return (0);
}
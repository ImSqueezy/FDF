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

int main(int argc, char **argv)
{
	g_data	gl;
	i_data	im;

	if (argc < 1)
		return (write(2, "Invalid number of arguments!", 28), 0);
	file_check(argv[1], &gl);
	connection_init(argv[1], &gl, &im);
	draw_onWin(&gl, &im);
	// system("leaks a.out");
	return (0);
}

// minilibx uses an extension which allows our program
// to share images with the Xwindow server through shared
// memory (/dev/shm)

// mlx_get_data_addr returns the address of the images
// as a simple array of pixels (char *)
// we navigate throught the string one byte at a time

// with images instead of mlx_pixel_put, we will be able to
// change the pixels directly using a pointer
// (way faster)

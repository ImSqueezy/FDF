/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:53:33 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/16 12:53:34 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#define SIZE_X 1200
#define SIZE_Y 1200

#include "Libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct image_data
{
	void *mlx_img;
	char *addr;
	int bp_pixel;
	int line_len;
	int endian;
} t_img;

typedef struct coordinates
{
	int x0;
	int y0;
	int x1;
	int y1;
	int color;
} t_coor;

typedef struct map_data
{
	int z;
	int color;
} t_map;

typedef struct global_data
{
	int width;
	int height;
	void *mlx_ptr;
	void *win_ptr;
	int zoom;
	int color;
	t_img img;
	t_map **map;
} t_gl;

int file_check(char *file, t_gl *data_ptr);
// void	line_draw(int x0, int y0, int x1, int y1, t_gl *gl_ptr);
void line_draw(t_coor c_ptr, t_gl *gl_ptr);
unsigned int ft_atoi_base(const char *str, const char *base);

#endif

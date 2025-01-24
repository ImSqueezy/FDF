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

#define SIZE_X 1600
#define SIZE_Y 1000

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
	void	*mlx_img;
	char	*addr;
	int		bp_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct point
{
	int	x;
	int	z;
	int	y;
	int	color;
}	t_point;

typedef struct map_data
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_map;

typedef struct global_data
{
	int		width;
	int		height;
	int		z_high;
	int 	z_min;
	void	*mlx_ptr;
	void	*win_ptr;
	int		zoom;
	t_img	img;
	t_map	**map;
}	t_gl;

int		file_check(char *file, t_gl *data);
void	line_draw(t_point p1, t_point p2, t_gl *gl_ptr);
int		mini_atoi_base(char *color);
void	pixel_put(t_gl *gl_ptr, int x, int y, int color);
int		draw(t_gl *gl_ptr);


int		hooks(t_gl *gl_ptr);

#endif


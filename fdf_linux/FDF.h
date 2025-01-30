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

#define SIZE_X 700
#define SIZE_Y 500
#define MASK 255
#define ISO_ANG 0.523599
#define BLACK 0x000000

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

typedef struct map_data
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_map;

typedef struct s_channels
{
	int	red;
	int	green;
	int	blue;
}	t_channel;

typedef struct s_map_colors
{
	int		base_color;
	int		high_altitude_color;
	int		low_altitude_color;
}	t_mc;

typedef struct global_data
{
	int		width;
	int		height;
	int		z_high;
	int 	z_min;
	void	*mlx_ptr;
	void	*win_ptr;
	float		zoom;
	int		iso;
	int		colored;
	t_img	img;
	t_mc	mc;
	t_map	**map;
}	t_gl;

void	file_check(char *file, t_gl *data);
void	line_draw(t_map p1, t_map p2, t_gl *gl_ptr);
int		mini_atoi_base(char *color);
void	pixel_put(t_gl *gl_ptr, int x, int y, int color);
int		draw(t_gl *gl_ptr);
int		linear_interpolation(t_map p1, t_map p2, int curr, int status);
int		hooks(t_gl *gl_ptr);

#endif



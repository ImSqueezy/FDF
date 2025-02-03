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
# define FDF_H

# define SIZE_X 1500
# define SIZE_Y 1100
# define BASE_COLOR 0x617D93
# define HIGH_COLOR 0x0F68A9
# define MED_COLOR 0x4D7898
# define BELOW_BASE 0x2E70A1
# define MASK 255
# define ISO_ANG 0.523599
# define BLACK 0x000000

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

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

typedef struct s_camera
{
	float	z_alti;
	float	x_scale;
	float	y_scale;
}	t_cam;

typedef struct matrices
{
	float	x;
	float	y;
	float	z;
}	t_mat;

typedef struct global_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title;
	int		width;
	int		height;
	int		z_max;
	int		z_min;
	float	zoom;
	int		colored;
	int		iso;
	int		bonus;
	t_cam	cam;
	t_img	img;
	t_map	**map;
	t_mat	*mat;
}	t_gl;

void	map_init(char *file, t_gl *data);
int		mini_atoi_base(char *color);
void	z_height_definition(int z, t_gl *data_ptr);

int		connection_init(char *map, t_gl *data);
int		connection_terminator(t_gl *data);
void	clear_map(t_gl *data, int last_index);

int		draw(t_gl *gl_ptr);
void	wireframe_instructions(t_gl *data);
void	background_filling(t_gl *data);
int		step_determiner(int change);
void	draw_vertically(t_map p1, t_map p2, t_gl *data);
void	draw_horizontally(t_map p1, t_map p2, t_gl *data);
int		color_definition(t_map p1, t_map p2, int curr, int status);

int		keybr_hooks(int keysysm, t_gl *gl_ptr);

#endif

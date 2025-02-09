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
# define GRAY 0x617D93
# define DARK_BLUE 0x0F68A9
# define BLUE 0x2E70A1
# define DARK_MODERATE_BLUE 0x4D7898
# define BASE_COLOR GRAY
# define HIGH_COLOR DARK_BLUE
# define MED_COLOR DARK_MODERATE_BLUE
# define BELOW_BASE BLUE
# define MASK 255
# define ISO_ANG 0.523599
# define BLACK 0x000000

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

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

typedef struct global_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title;
	int		width;
	int		height;
	int		z_max;
	int		z_min;
	int		colored;
	int		iso;
	int		bonus;
	int		rotation;
	float	zoom;
	float	x_angl;
	float	y_angl;
	float	z_angl;
	t_cam	cam;
	t_img	img;
	t_map	**map;
}	t_gl;

void	map_init(char *file, int fd, t_gl *data);
int		mini_atoi_base(char *color);
int		words_counter(char *line);
void	clear_double(char **ptr);
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
void	rotate_y(t_map *p, t_gl *data);
void	rotate_x(t_map *p, t_gl *data);
void	rotate_z(t_map *p, t_gl *data);
void	rotation_hooks(int code, t_gl *data);

#endif

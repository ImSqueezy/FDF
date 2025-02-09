/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:44:20 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/23 19:44:23 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void	isomet(t_map *p)
{
	int	tmp;

	tmp = p->x;
	p->x = ((p->x - p->y) * cos(ISO_ANG));
	p->y = (tmp + p->y) * sin(ISO_ANG) - p->z;
}

static void	plot_line(t_map p1, t_map p2, t_gl *gl_ptr)
{
	int	run;
	int	rise;

	run = p2.x - p1.x;
	rise = p2.y - p1.y;
	if (abs(run) > abs(rise))
		draw_horizontally(p1, p2, gl_ptr);
	else
		draw_vertically(p1, p2, gl_ptr);
}

static void	data_coloring(t_map *p, t_gl *data)
{
	if (!data->colored)
	{
		if (p->z > data->z_min && p->z != data->z_max)
			p->color = MED_COLOR;
		if (p->z == data->z_max)
			p->color = HIGH_COLOR;
		else if (p->z < data->z_min)
			p->color = BELOW_BASE;
	}
}

static t_map	scale(t_map p, t_gl *gl_ptr)
{
	data_coloring(&p, gl_ptr);
	p.x = (p.x - gl_ptr->width / 2) * gl_ptr->zoom;
	p.y = (p.y - gl_ptr->height / 2) * gl_ptr->zoom;
	p.z = (p.z * gl_ptr->zoom) * gl_ptr->cam.z_alti;
	if (gl_ptr->rotation && (gl_ptr->width < 100 || gl_ptr->height < 100))
	{
		rotate_y(&p, gl_ptr);
		gl_ptr->x_angl += 0.000008;
	}
	else if (!gl_ptr->rotation)
	{
		rotate_x(&p, gl_ptr);
		rotate_y(&p, gl_ptr);
		rotate_z(&p, gl_ptr);
	}
	if (gl_ptr->iso == 1)
		isomet(&p);
	p.x += SIZE_X / 2 + gl_ptr->cam.x_scale;
	p.y += SIZE_Y / 2 + gl_ptr->cam.y_scale;
	return (p);
}

int	draw(t_gl *gl_ptr)
{
	int	i;
	int	j;

	if (!gl_ptr->win_ptr)
		return (0);
	background_filling(gl_ptr);
	i = -1;
	while (++i < gl_ptr->height)
	{
		j = -1;
		while (++j < gl_ptr->width)
		{
			if (j < gl_ptr->width - 1)
				plot_line(scale(gl_ptr->map[i][j], gl_ptr),
					scale(gl_ptr->map[i][j + 1], gl_ptr), gl_ptr);
			if (i < gl_ptr->height - 1)
				plot_line(scale(gl_ptr->map[i][j], gl_ptr),
					scale(gl_ptr->map[i + 1][j], gl_ptr), gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	wireframe_instructions(gl_ptr);
	return (0);
}

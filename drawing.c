/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:56:22 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/06 15:56:24 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void	pixel_put(t_gl *gl_ptr, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pxl = gl_ptr->img.addr + (y * gl_ptr->img.line_len
				+ x * (gl_ptr->img.bp_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}

static void	draw(int x_step, int y_step, t_coor *c_ptr, t_gl *gl_ptr)
{
	int	dx;
	int	dy;
	int	error;
	int	e2;

	dx = abs(c_ptr->x1 - c_ptr->x0);
	dy = -abs(c_ptr->y1 - c_ptr->y0);
	error = dx + dy;
	while (!(c_ptr->x0 == c_ptr->x1 && c_ptr->y0 == c_ptr->y1))
	{
		pixel_put(gl_ptr, c_ptr->x0 + SIZE_X / 2, c_ptr->y0 + SIZE_Y/2, gl_ptr->color);
		e2 = 2 * error;
		if (e2 >= dy)
		{
			error += dy;
			c_ptr->x0 += x_step;
		}
		else if (e2 <= dx)
		{
			error += dx;
			c_ptr->y0 += y_step;
		}
	}
}

void	isomet(int *x, int *y, int z, t_gl *gl_ptr)
{
	float	ang;

	ang = 0.5;
	*x = (*x * gl_ptr->zoom) - (gl_ptr->width/2 * gl_ptr->zoom);
	*y = (*y * gl_ptr->zoom) - (gl_ptr->height/2 * gl_ptr->zoom);
	z *= gl_ptr->zoom;
	*x = (*x - *y) * cos(ang);
	*y = (*x + *y) * sin(ang) - z;
}

void	coor_coloring(t_coor *c, t_gl *gl_ptr)
{
	if (!gl_ptr->map[c->y0][c->x0].z && !gl_ptr->map[c->y1][c->x1].z)
		gl_ptr->color = 0xffffff;
	else
		gl_ptr->color = gl_ptr->map[c->y0][c->x0].color;
}

void	line_draw(t_coor c, t_gl *gl_ptr)
{
	int	xs;
	int	ys;

	coor_coloring(&c, gl_ptr);
	isomet(&c.x0, &c.y0, gl_ptr->map[c.y0][c.x0].z, gl_ptr);
	isomet(&c.x1, &c.y1, gl_ptr->map[c.y1][c.x1].z, gl_ptr);
	if (c.x0 < c.x1)
		xs = 1;
	else
		xs = -1;
	if (c.y0 < c.y1)
		ys = 1;
	else
		ys = -1;
	draw(xs, ys, &c, gl_ptr);
}
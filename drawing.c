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
		pixel_put(gl_ptr, (c_ptr->x0 + SIZE_X / 2)
			- (gl_ptr->width * gl_ptr->zoom) / 2, (c_ptr->y0 + SIZE_Y / 2)
			- (gl_ptr->height * gl_ptr->zoom) / 2, c_ptr->color);
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

void	isomet(t_coor *c_ptr, t_gl *gl_ptr)
{
	float ang = 0.523599;
	c_ptr->x0 = c_ptr->x0 * 1 + c_ptr->y0 * 0 + gl_ptr->map[c_ptr->y0][c_ptr->x0].z * 0;
	c_ptr->y0 = (c_ptr->x0 * 0) + c_ptr->y0 * cos(ang) + gl_ptr->map[c_ptr->y0][c_ptr->x0].z * sin(ang);
	gl_ptr->map[c_ptr->y0][c_ptr->x0].z = c_ptr->x0 * 0 + c_ptr->y0 * -sin(ang) + gl_ptr->map[c_ptr->y0][c_ptr->x0].z * cos(ang);

}

void	zoom(t_coor *c_ptr, t_gl *gl_ptr)
{
	c_ptr->x0 *= gl_ptr->zoom;
	c_ptr->y0 *= gl_ptr->zoom;
	c_ptr->x1 *= gl_ptr->zoom;
	c_ptr->y1 *= gl_ptr->zoom;
}

void	line_draw(t_coor c, t_gl *gl_ptr)
{
	int	xs;
	int	ys;

	isomet(&c, gl_ptr);
	zoom(&c, gl_ptr);
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

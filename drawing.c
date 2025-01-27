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

void	pixel_put(t_gl *gl_ptr, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pxl = gl_ptr->img.addr + (y * gl_ptr->img.line_len
				+ x * (gl_ptr->img.bp_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}

void	isomet(t_point *p, t_gl *gl_ptr)
{
	float	ang;

	ang = 1;
	p->x = (p->x - p->y) * cos(ang) + SIZE_X/2;
	p->y = (p->x + p->y) * sin(ang) - p->z + SIZE_Y/2;
}

int	color_def(t_point p1, t_point p2, int curr, int status)
{
	if (p1.z || p2.z)
		return (linear_interpolation(p1, p2, curr,status));
	return (p1.color);
}


void	drawV(t_point p1, t_point p2, t_gl *data)
{
	int	dx;
	int dy;
	int decition;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2 * abs(dx) - abs(dy);
	while (p1.y != p2.y)
	{
		if (decition < 0)
			decition = decition + 2*abs(dx);
		else
		{
			if (dx > 0)
				p1.x++;
			else
				p1.x--;
			decition = decition + 2*abs(dx) - 2*abs(dy);
		}
		if (dy > 0)
			p1.y++;
		else
			p1.y--;
		pixel_put(data, p1.x, p1.y, color_def(p1, p2, p1.y, 1));
	}
}

void	drawH(t_point p1, t_point p2, t_gl *data)
{
	int	dx;
	int	dy;
	int	decition;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2*abs(dy) - abs(dx);
	while (p1.x != p2.x)
	{
		if (decition < 0)
			decition = decition + 2 *abs(dy);
		else
		{
			if (dy > 0)
				p1.y++;
			else
				p1.y--;
			decition = decition + 2*abs(dy) - 2 * abs(dx);
		}
		if (dx > 0)
			p1.x++;
		else
			p1.x--;
		pixel_put(data, p1.x, p1.y, color_def(p1, p2, p1.x, 0));
	}
}

void plotLine(t_point p1, t_point p2, t_gl *gl_ptr)
{
	int	run;
	int	rise;

	run = p2.x - p1.x;
	rise = p2.y - p1.y;
	if (abs(run) > abs(rise))
		drawH(p1, p2, gl_ptr);
	else
		drawV(p1, p2, gl_ptr);
}
  
t_point	t_point_init(int i, int j, t_gl *gl_ptr)
{
	t_point p;

	p.x = (gl_ptr->map[i][j].x * gl_ptr->zoom) + SIZE_X/2;
	p.y = (gl_ptr->map[i][j].y * gl_ptr->zoom) + SIZE_Y/2;
	p.z = gl_ptr->map[i][j].z;
	p.color = gl_ptr->map[i][j].color;
	return (p);
}

int	draw(t_gl *gl_ptr)
{
	int	i;
	int	j;

	if (!gl_ptr->win_ptr)
		return (0);
	i = -1;
	while (++i < gl_ptr->height)
	{
		j = -1;
		while (++j < gl_ptr->width)
		{
			if (j < gl_ptr->width - 1)
				plotLine(t_point_init(i, j, gl_ptr),
				t_point_init(i, j + 1, gl_ptr), gl_ptr);
			if (i < gl_ptr->height - 1)
				plotLine(t_point_init(i, j, gl_ptr),
				t_point_init(i + 1, j, gl_ptr), gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

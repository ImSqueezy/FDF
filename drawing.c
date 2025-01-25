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

// static void	draw(int x_step, int y_step, t_gl *gl_ptr)
// {
// 	int	dx;
// 	int	dy;
// 	int	error;
// 	int	e2;

// }
	// isomet(&c.x0, &c.y0, gl_ptr->map[c.y0][c.x0].z, gl_ptr);
	// isomet(&c.x1, &c.y1, gl_ptr->map[c.y1][c.x1].z, gl_ptr);

void	isomet(t_point p, t_gl *gl_ptr)
{
	float	ang;

	ang = 0.5;
	p.x = (p.x * gl_ptr->zoom) - (gl_ptr->zoom);
	p.y = (p.y * gl_ptr->zoom) - (gl_ptr->zoom);
	p.z *= gl_ptr->zoom;
	p.x = (p.x - p.y) * cos(ang);
	p.y = (p.x + p.y) * sin(ang) - p.z;
}

void	step_determiner(t_point p1, t_point p2, int *x_step, int *y_step)
{
	if (p1.x < p2.x)
		*x_step = 1;
	else
		*x_step = -1;
	if (p1.y < p2.y)
		*y_step = 1;
	else
		*y_step = -1;
}

int	color_def(t_point p1, t_point p2)
{
	if (p1.z || p2.z)
		return (0xff0000);
	return (p1.color);
}


void	draw_higher_slope(t_point p1, t_point p2, t_gl *data)
{
	int	dx;
	int dy;
	int decition;
	int i;

	i = 0;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2 * abs(dx) - abs(dy);
	while (i < abs(dy))
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
		pixel_put(data, p1.x, p1.y, color_def(p1, p2));
		i++;
	}
}

void	draw_lower_slope(t_point p1, t_point p2, t_gl *data)
{
	int	dx;
	int	dy;
	int	decition;
	int	i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	i = 0;
	decition = 2*abs(dy) - abs(dx);
	while (i < abs(dx))
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
		pixel_put(data, p1.x, p1.y, color_def(p1, p2));
		i++;
	}
}

void drawing_algo(t_point p1, t_point p2, t_gl *gl_ptr)
{
   int dx =  abs(p2.x-p1.x), sx = p1.x<p2.x ? 1 : -1;
   int dy = -abs(p2.y-p1.y), sy = p1.y<p2.y ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      pixel_put(gl_ptr,p1.x,p1.y, color_def(p1, p2));
      if (p1.x==p2.x && p1.y==p2.y) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; p1.x += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; p1.y += sy; } /* e_xy+e_y < 0 */
   }
}

void plotLine(t_point p1, t_point p2, t_gl *gl_ptr)
{
	int	dx;
	int	dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		draw_lower_slope(p1, p2, gl_ptr);
	else
		draw_higher_slope(p1, p2, gl_ptr);
}
  

t_point	change_point(int i, int j, t_gl *gl_ptr)
{
	t_point p;

	// for top view i would remove - gl_ptr->map[i][j].z
	p.x = (gl_ptr->map[i][j].x * gl_ptr->zoom - gl_ptr->map[i][j].z) + SIZE_X/2;
	p.y = gl_ptr->map[i][j].y * gl_ptr->zoom - gl_ptr->map[i][j].z + SIZE_Y/2;
	p.z = gl_ptr->map[i][j].z;
	p.color = gl_ptr->map[i][j].color;
	// isomet(p, gl_ptr);
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
				plotLine(change_point(i, j, gl_ptr), change_point(i, j + 1, gl_ptr), gl_ptr);
				// plotLine((t_point){10, 0, 10, 0xff0000}, (t_point){10, 0, 20, 0xff0000}, gl_ptr);
				// drawing_algo(change_point(i, j, gl_ptr), change_point(i, j + 1, gl_ptr), gl_ptr);
			if (i < gl_ptr->height - 1)
				plotLine(change_point(i, j, gl_ptr), change_point(i + 1, j, gl_ptr), gl_ptr);
				// drawing_algo(change_point(i, j, gl_ptr), change_point(i + 1, j, gl_ptr), gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

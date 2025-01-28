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

void	isomet(t_map *p)
{
	int	tmp;

	tmp = p->x;
	p->x = ((p->x - p->y) * cos(ISO_ANG)) + SIZE_X/2;
	p->y = (tmp + p->y) * sin(ISO_ANG) - p->z + SIZE_Y/2;
}

void	drawV(t_map p1, t_map p2, t_gl *data)
{
	int	dx;
	int dy;
	int decition;
	t_map	current;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2 * abs(dx) - abs(dy);
	current = p1;
	while (current.y != p2.y)
	{
		if (decition < 0)
			decition = decition + 2*abs(dx);
		else
		{
			if (dx > 0)
				current.x++;
			else
				current.x--;
			decition = decition + 2*abs(dx) - 2*abs(dy);
		}
		if (dy > 0)
			current.y++;
		else
			current.y--;
		pixel_put(data, current.x, current.y, linear_interpolation(p1, p2, current.y, 1));
	}
}

void	drawH(t_map p1, t_map p2, t_gl *data)
{
	int	dx;
	int	dy;
	int	decition;
	t_map	current;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2*abs(dy) - abs(dx);
	current = p1;
	while (current.x != p2.x)
	{
		if (decition < 0)
			decition = decition + 2 *abs(dy);
		else
		{
			if (dy > 0)
				current.y++;
			else
				current.y--;
			decition = decition + 2*abs(dy) - 2 * abs(dx);
		}
		if (dx > 0)
			current.x++;
		else
			current.x--;
		pixel_put(data, current.x, current.y, linear_interpolation(p1, p2, current.x, 0));
	}
}

// int	which_step(int *change, int difference)
// {
// 	*change = difference;
// 	if (*change > 0)
// 		return (1);
// 	return (-1);
// }

// void plotLine(t_map p1, t_map p2, t_gl *data)
// {
// 	int	run;
// 	int	rise;
// 	int x_step;
// 	int y_step;
// 	int	err;
// 	int	e2;

// 	x_step = which_step(&run, abs(p2.x - p1.x));
// 	y_step = which_step(&rise, -abs(p2.y - p1.y));
// 	err = run + rise;
// 	// printf("here\n");
// 	// printf("%d %d && %d %d\n", p1.x, p2.y, p1.y, p2.y);
// 	while (p1.x != p2.x && p1.y != p2.y)
// 	{
// 		printf("%d\n", p1.x);
// 		pixel_put(data, p1.x, p2.y, 0xffffff);
// 		e2 = 2 * err;
// 		if (e2 >= rise)
// 		{
// 			err += rise;
// 			p1.x += x_step;
// 		}
// 		if (e2 <= run)
// 		{
// 			err += run;
// 			p1.y += y_step;
// 		}
// 	}
// }

void plotLine(t_map p1, t_map p2, t_gl *gl_ptr)
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
  
t_map	scale(t_map p, t_gl *gl_ptr)
{
	if (gl_ptr->iso == 0)
	{
		p.x = (p.x - gl_ptr->width/2) * gl_ptr->zoom + SIZE_X/2;
		p.y = (p.y - gl_ptr->height/2) * gl_ptr->zoom + SIZE_Y/2;
	}
	else
	{
		p.x = (p.x - gl_ptr->width/2) * gl_ptr->zoom;
		p.y = (p.y - gl_ptr->height/2) * gl_ptr->zoom;
		isomet(&p);
	}
	return (p);
}

void	background_filling(t_gl *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE_Y)
	{
		j = 0;
		while (j < SIZE_X)
		{
			pixel_put(data, j, i, BLACK);
			j++;
		}
		i++;
	}
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
				plotLine(scale(gl_ptr->map[i][j], gl_ptr), scale(gl_ptr->map[i][j + 1], gl_ptr), gl_ptr);
			if (i < gl_ptr->height - 1)
				plotLine(scale(gl_ptr->map[i][j], gl_ptr), scale(gl_ptr->map[i + 1][j],gl_ptr), gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

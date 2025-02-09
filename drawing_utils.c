/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:25:53 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/03 12:25:55 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void	pixel_put(t_gl *data, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pxl = data->img.addr + (y * data->img.line_len
				+ x * (data->img.bp_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}

int	step_determiner(int change)
{
	if (change > 0)
		return (1);
	return (-1);
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

void	draw_vertically(t_map p1, t_map p2, t_gl *data)
{
	int		dx;
	int		dy;
	int		decition;
	t_map	current;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2 * abs(dx) - abs(dy);
	current = p1;
	while (current.y != p2.y)
	{
		pixel_put(data, current.x, current.y,
			color_definition(p1, p2, current.y, 1));
		if (decition < 0)
			decition = decition + 2 * abs(dx);
		else
		{
			current.x += step_determiner(dx);
			decition = decition + 2 * abs(dx) - 2 * abs(dy);
		}
		current.y += step_determiner(dy);
	}
}

void	draw_horizontally(t_map p1, t_map p2, t_gl *data)
{
	int		dx;
	int		dy;
	int		decition;
	t_map	current;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	decition = 2 * abs(dy) - abs(dx);
	current = p1;
	while (current.x != p2.x)
	{
		pixel_put(data, current.x, current.y,
			color_definition(p1, p2, current.x, 0));
		if (decition < 0)
			decition = decition + 2 * abs(dy);
		else
		{
			current.y += step_determiner(dy);
			decition = decition + 2 * abs(dy) - 2 * abs(dx);
		}
		current.x += step_determiner(dx);
	}
}

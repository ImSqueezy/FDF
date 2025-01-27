	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_definition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:21:08 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/27 10:21:09 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static double get_fraction(int p1, int p2, int curr)
{
	if (p2 == p1)
		return (0);
	return ((double)(curr - p1)/(double)(p2 - p1));
}

int	calc_color_channel(int start, int end, double percentage)
{
	int	color_channel;

	color_channel = (1 - percentage) * start + percentage * end;
	return (color_channel);
}

int	linear_interpolation(t_point p1, t_point p2, int curr, int status)
{
	float	fraction;
	int		green, red, blue;
	int		current_color;

	if (status) // working with y
		fraction = get_fraction(p1.y, p2.y, curr);
	else
		fraction = get_fraction(p1.x, p2.x, curr);
	printf("%f\n", fraction);
	current_color = p1.color * (1 - fraction) + p2.color;
	return (current_color);
}

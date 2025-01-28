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

static double	get_fraction(int p1, int p2, int curr)
{
	return ((double)(curr - p1)/(double)(p2 - p1));
}

static int	interpolate(int start, int end, double percentage)
{
	int	color_channel;

	color_channel = (1 - percentage) * start + percentage * end;
	return (color_channel);
}

static void	package_color_channels(t_channel c1, t_channel c2, t_channel *curr, double fraction)
{
	(*curr).red = interpolate(c1.red, c2.red, fraction);
	(*curr).green = interpolate(c1.green, c2.green, fraction);
	(*curr).blue = interpolate(c1.blue, c2.blue, fraction);
}

static void	split_color_channels(int color, t_channel *ptr)
{
	ptr->red = color >> 16 & MASK;
	ptr->green = color >> 8 & MASK;
	ptr->blue = color & MASK;
}

int	linear_interpolation(t_map p1, t_map p2, int curr, int status)
{
	float	fraction;
	t_channel	curr_chan;
	t_channel	p1_chan;
	t_channel	p2_chan;

	if (status)
		fraction = get_fraction(p1.y, p2.y, curr);
	else
		fraction = get_fraction(p1.x, p2.x, curr);
	split_color_channels(p1.color, &p1_chan);
	split_color_channels(p2.color, &p2_chan);
	package_color_channels(p1_chan, p2_chan, &curr_chan, fraction);
	return ((curr_chan.red << 16) | (curr_chan.green << 8) | curr_chan.blue);
}

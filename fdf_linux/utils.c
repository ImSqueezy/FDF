/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:03:03 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/03 12:03:04 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int	mini_atoi_base(char *line)
{
	int		result;
	char	c;

	line += 2;
	result = 0;
	while (*line)
	{
		c = ft_tolower(*line);
		if (c >= '0' && c <= '9')
			result = result * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + (c - 'a' + 10);
		else
			break ;
		line++;
	}
	return (result);
}

int	words_counter(char *line)
{
	int	i;
	int	width;

	width = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] != ' ' && line[i] != '\n') && (line[i + 1] == '\n'
				|| line[i + 1] == ' ' || line[i + 1] == '\0'))
			width++;
	}
	return (width);
}

void	z_height_definition(int z, t_gl *data_ptr)
{
	if (z > data_ptr->z_max)
		data_ptr->z_max = z;
	else if (z < data_ptr->z_min)
		data_ptr->z_min = z;
}

void	view_status(t_gl *data)
{
	if (data->iso)
		mlx_string_put(data->mlx_ptr, data->win_ptr, SIZE_X / 2 - 30, 30,
			0xffffff, "ISOMETRIC VIEW");
	else
		mlx_string_put(data->mlx_ptr, data->win_ptr, SIZE_X / 2 - 30, 30,
			0xffffff, "ORTHO VIEW");
	if (!data->bonus)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 30, 0xffffff,
			"TOGGLE BONUS: B");
}

void	wireframe_instructions(t_gl *data)
{
	view_status(data);
	if (data->bonus)
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 30, 0xffffff,
			"TOGGLE PROJECTION VIEWS: T");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 50, 0xffffff,
			"TOGGLE ANIMATION (MAP_WIDTH < 100): SPACE");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 70, 0xffffff,
			"ZOOMING: - / +");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 90, 0xffffff,
			"ALTITUDE MANIPULATION: J / K");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 110, 0xffffff,
			"TRANSPARENT BASE: N (MAP WIDTH < 100)");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 130, 0xffffff,
			"ROTATIONS: W / S / A / D / Q / E");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 150, 0xffffff,
			"TRANSLATIONS: Y / V / G / H");
	}
}

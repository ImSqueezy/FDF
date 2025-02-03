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

void	z_height_definition(int z, t_gl *data_ptr)
{
	if (z > data_ptr->z_max)
		data_ptr->z_max = z;
	else if (z < data_ptr->z_min)
		data_ptr->z_min = z;
}

void	clear_map(t_gl *data, int last_index)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (i < last_index)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void	wireframe_instructions(t_gl *data)
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
	else
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 30, 0xffffff,
			"TOGGLE PROJECTION VIEWS: T");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 50, 0xffffff,
			"ZOOM MANIPULATION: - / +");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 90, 0xffffff,
			"ALTITUDE MANIPULATION: J / K");
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 70, 0xffffff,
			"TRANSPARENT BASE: N");
	}
}

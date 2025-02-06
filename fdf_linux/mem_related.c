/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:48 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/06 10:48:50 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	clear_double(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
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

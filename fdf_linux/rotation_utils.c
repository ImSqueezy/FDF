/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:58:59 by aouaalla          #+#    #+#             */
/*   Updated: 2025/02/04 19:59:23 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	rotate_y(t_map *p, t_gl *data)
{
	int	tmp;

	tmp = p->x;
	p->x = p->x * cos(data->x_angl) + p->z * sin(data->x_angl);
	p->z = tmp * -sin(data->x_angl) + p->z * cos(data->x_angl);
}

void	rotate_x(t_map *p, t_gl *data)
{
	int	tmp;

	tmp = p->y;
	p->y = p->y * cos(data->y_angl) + p->z * -sin(data->y_angl);
	p->z = tmp * sin(data->y_angl) + p->z * cos(data->y_angl);
}

void	rotate_z(t_map *p, t_gl *data)
{
	int	tmp;

	tmp = p->x;
	p->x = p->x * cos(data->z_angl) + p->y * -sin(data->z_angl);
	p->y = tmp * sin(data->z_angl) + p->y * cos(data->z_angl);
}

void	rotation_hooks(int code, t_gl *data)
{
	if (code == XK_d)
		data->x_angl += 0.02;
	else if (code == XK_a)
		data->x_angl -= 0.02;
	else if (code == 32 && !data->rotation)
		data->rotation = 1;
	else if (code == 32 && data->rotation)
	{
		data->rotation = 0;
		data->x_angl = 0.008;
	}
	else if (code == XK_w)
		data->y_angl += 0.02;
	else if (code == XK_s)
		data->y_angl -= 0.02;
	else if (code == XK_q)
		data->z_angl += 0.02;
	else if (code == XK_e)
		data->z_angl -= 0.02;
}

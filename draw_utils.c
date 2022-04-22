/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:01:23 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/22 18:53:43 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	position(t_coordinates *pos_tmp)
{
	pos_tmp->x += 300;
	pos_tmp->y += 200;
	pos_tmp->x1 += 300;
	pos_tmp->y1 += 200;
}

void	color(t_coordinates *pos_tmp, t_fdf *data)
{
	if (data->z_matrix[(int)pos_tmp->y][(int)pos_tmp->x] ||
	data->z_matrix[(int)pos_tmp->y1][(int)pos_tmp->x1])
		data->color = 0xff4500;
	else
		data->color = 0xffffff;
}

// void	isometric(t_coordinates *pos) почему-то не работает можно пофиксить
// {
// 	int	x_tmp;

// 	x_tmp = (int)pos->x;
// 	pos->x = (pos->x - pos->y) * cos(0.523599);
// 	pos->y = (x_tmp + pos->y) * sin(0.523599) - pos->z_pos;
// 	x_tmp = (int)pos->x1;
// 	pos->x1 = (pos->x1 - pos->y) * cos(0.523599);
// 	pos->y1 = (x_tmp + pos->y1) * sin(0.523599) - pos->z1_pos;
// }

void	isometric(t_coordinates *pos, int flag)
{
	int	x_tmp;

	if (flag == 1)
	{
		x_tmp = (int)pos->x;
		pos->x = (pos->x - pos->y) * cos(0.523599);
		pos->y = (x_tmp + pos->y) * sin(0.523599) - pos->z_pos;
	}
	else
	{
		x_tmp = (int)pos->x1;
		pos->x1 = (pos->x1 - pos->y1) * cos(0.523599);
		pos->y1 = (x_tmp + pos->y1) * sin(0.523599) - pos->z1_pos;
	}
}

void	zoom(t_coordinates *pos_tmp, t_fdf *data)
{
	if (data->width > 9)
		data->zoom = (int)rintf(55 / rintf((float) data->width / 10));
	else
		data->zoom = 20;
	pos_tmp->x *= data->zoom;
	pos_tmp->x1 *= data->zoom;
	pos_tmp->y *= data->zoom;
	pos_tmp->y1 *= data->zoom;
}

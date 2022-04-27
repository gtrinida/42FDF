/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:01:23 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/27 15:31:06 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	position(t_coordinates *pos_tmp)
{
	pos_tmp->x += 600;
	pos_tmp->y += 300;
	pos_tmp->x1 += 600;
	pos_tmp->y1 += 300;
}

void	color(t_coordinates *pos_tmp, t_fdf *data)
{
	if (data->z_matrix[(int)pos_tmp->y][(int)pos_tmp->x] ||
	data->z_matrix[(int)pos_tmp->y1][(int)pos_tmp->x1])
		data->color = 0xff4500;
	else
		data->color = 0xffffff;
}

void	isometric(t_coordinates *pos, int flag)
{
	int	x_tmp;

	if (flag == 1)
	{
		x_tmp = (int)pos->x;
		pos->x = (pos->x - pos->y) * cos(0.6);
		pos->y = (x_tmp + pos->y) * sin(0.6) - pos->z_pos;
	}
	else
	{
		x_tmp = (int)pos->x1;
		pos->x1 = (pos->x1 - pos->y1) * cos(0.6);
		pos->y1 = (x_tmp + pos->y1) * sin(0.6) - pos->z1_pos;
	}
}

void	zoom(t_coordinates *pos_tmp, t_fdf *data)
{
	if (data->width > 9)
		data->zoom = (int)rintf(55 / rintf((float) data->width / 10));
	else
		data->zoom = 50;
	pos_tmp->x *= data->zoom;
	pos_tmp->x1 *= data->zoom;
	pos_tmp->y *= data->zoom;
	pos_tmp->y1 *= data->zoom;
}

void	work_with_win(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1200, 1000, "FDF");
	data->img->img = mlx_new_image(data->mlx_ptr, 1200, 1000);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel,
			&data->img->line_length, &data->img->endian);
}

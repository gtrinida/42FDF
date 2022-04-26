/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:17:16 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/26 15:03:44 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	max_steps(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

float	sign(float i)
{
	if (i < 0)
		return (i *= -1);
	else
		return (i);
}

void	draw_line(t_coordinates *pos, t_fdf *data)
{
	t_coordinates	pos_tmp;
	float			x_steps;
	float			y_steps;
	int				max;

	pos_tmp = *pos;
	pos_tmp.z_pos = data->z_matrix[(int)pos_tmp.y][(int)pos_tmp.x];
	pos_tmp.z1_pos = data->z_matrix[(int)pos_tmp.y1][(int)pos_tmp.x1];
	zoom(&pos_tmp, data);
	isometric(&pos_tmp, 1);
	isometric(&pos_tmp, 2);
	color(pos, data);
	position(&pos_tmp);
	x_steps = pos_tmp.x1 - pos_tmp.x;
	y_steps = pos_tmp.y1 - pos_tmp.y;
	max = max_steps(sign(x_steps), sign(y_steps));
	x_steps /= max;
	y_steps /= max;
	while ((int)(pos_tmp.x - pos_tmp.x1) || (int)(pos_tmp.y - pos_tmp.y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)pos_tmp.x,
			(int)pos_tmp.y, data->color);
		pos_tmp.x += x_steps;
		pos_tmp.y += y_steps;
	}
}

void	draw_matrix_utils(t_fdf *data, t_coordinates *pos)
{
	pos->x = 0;
	while (pos->x < data->width)
	{
		if (pos->x < data->width - 1)
		{
			pos->x1 = pos->x + 1;
			pos->y1 = pos->y;
			draw_line(pos, data);
		}
		if (pos->y < data->height - 1)
		{
			pos->x1 = pos->x;
			pos->y1 = pos->y + 1;
			draw_line(pos, data);
		}
		pos->x++;
	}
	pos->y++;
}

int	draw_matrix(t_fdf *data)
{
	t_coordinates	*pos;

	pos = malloc(sizeof(t_coordinates));
	if (!pos)
		return (0);
	pos_init(pos);
	while (pos->y < data->height)
		draw_matrix_utils(data, pos);
	free(pos);
	return (1);
}

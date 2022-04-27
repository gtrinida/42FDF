/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:17:16 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/27 15:57:03 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_img(t_img *prm, int x, int y, int color)
{
	char	*dst;

	if (x > 1199 || y > 999 || x < 0 || y < 0)
		return ;
	dst = prm->addr + (y * prm->line_length + x * (prm->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	max_steps(float x, float y)
{
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	if (x > y)
		return (x);
	else
		return (y);
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
	max = max_steps(x_steps, y_steps);
	x_steps /= max;
	y_steps /= max;
	while ((int)(pos_tmp.x - pos_tmp.x1) || (int)(pos_tmp.y - pos_tmp.y1))
	{
		put_pixel_img(data->img, (int)roundl(pos_tmp.x),
			(int)roundl(pos_tmp.y), data->color);
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

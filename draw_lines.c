/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/22 15:57:54 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_color(t_fdf *data, t_basic *pos)
{
	if (data->z_matrix[(int)pos->y][(int)pos->x] ||
	data->z_matrix[(int)pos->y1][(int)pos->x1])
		data->color = 0xff4500;// 0xa020f0;
	else
		data->color = 0xffffff;
}

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

void	isometric(float x, float y, int z)
{
//	int x_tmp;

//	x_tmp = (int)x;
	x = (x - y) * cos (0.8);
	y = (x + y) * sin (0.8) - z;
}

void get_3d(t_basic *pos, int z_pos, int flag)
{
	int x_tmp;
	
	if (flag == 1)
	{
		x_tmp = (int)pos->x;
		pos->x = (pos->x - pos->y) * cos(0.523599);//завести tmp для икса
		pos->y = (x_tmp + pos->y) * sin(0.523599) - z_pos;
	}
	else
	{
		x_tmp = (int)pos->x1;
		pos->x1 = (pos->x1 - pos->y1) * cos(0.523599);//завести tmp для икса
		pos->y1 = (x_tmp + pos->y1) * sin(0.523599) - z_pos;
	}
}

void get_zoom(t_basic *pos, t_fdf *data)
{
	pos->x *= data->zoom;
	pos->x1 *= data->zoom;
	pos->y *= data->zoom;
	pos->y1 *= data->zoom;
}

void	draw_lines(t_basic *pos, t_fdf *data)
{
	t_basic	pos_tmp;
	float	x_steps;
	float	y_steps;
	int		max;
	int		z;
	int		z1;

	pos_tmp = *pos;
	z = data->z_matrix[(int)pos_tmp.y][(int)pos_tmp.x];
	z1 = data->z_matrix[(int)pos_tmp.y1][(int)pos_tmp.x1];
	get_zoom(&pos_tmp, data);
	get_3d(&pos_tmp, z, 1);
	get_3d(&pos_tmp, z1, 2);
	get_color(data, pos);
	pos_tmp.x += 300;
	pos_tmp.y += 200;
	pos_tmp.x1 += 300;
	pos_tmp.y1 += 200;
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

void	draw_matrix(t_fdf *data)
{
	t_basic	*pos;

	pos = malloc(sizeof(t_basic));
	if (!pos)
		return ;
	pos_init(pos);
		if (data->width > 9)
		data->zoom = (int)rintf(55 / rintf((float) data->width / 10));
	else
		data->zoom = 20;	
	while (pos->y < data->height - 1)
	{
		pos->x = 0;
		while (pos->x < data->width - 1)
		{
			//is_it_voluminous(data, pos);
			pos->x1 = pos->x + 1;
			pos->y1 = pos->y;
			if (pos->x < data->width - 1)
				draw_lines(pos, data);
			pos->x1 = pos->x;
			pos->y1 = pos->y + 1;
			if (pos->y < data->width - 1)
				draw_lines(pos, data);
			pos->x++;
		}
		pos->x1 = pos->x;
		pos->y1 = pos->y + 1;
		draw_lines(pos, data);
		pos->y++;
	}
	pos->x = 0;
	draw_lines(pos, data);
}

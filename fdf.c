/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/27 15:28:00 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_matrix(t_fdf *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->z_matrix[i]);
		i++;
	}
	free(data->z_matrix);
	free(data->img);
	free(data);
}

void	initialize(t_fdf *data)
{
	data->height = 0;
	data->width = 0;
	data->z_matrix = 0;
	data->win_ptr = 0;
	data->mlx_ptr = 0;
	data->zoom = 0;
}

int	close_window(int key, t_fdf *data)
{
	if (key == KEY_EXIT)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		clean_matrix(data);
		exit(0);
	}
	return (0);
}

int	stop_process(t_fdf *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	clean_matrix(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
	{
		write(1, "Invalid number of arguments\n", 28);
		return (0);
	}
	data = malloc(sizeof(t_fdf));
	data->img = malloc(sizeof(t_img));
	if (!data || !data->img)
		return (0);
	initialize(data);
	if (!valid_format(argv[1]) || !read_file(argv[1], data))
	{
		write(1, "Invalid file name or the file is empty\n", 39);
		free(data->img);
		free(data);
		return (0);
	}
	work_with_win(data);
	draw_matrix(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
	mlx_hook(data->win_ptr, 2, 1L << 0, close_window, data);
	mlx_hook(data->win_ptr, 17, 0, stop_process, data);
	mlx_loop(data->mlx_ptr);
}

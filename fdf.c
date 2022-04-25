/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/25 13:54:48 by gtrinida         ###   ########.fr       */
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

// int	close(int key, t_fdf *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc < 2)
		return (0);
	data = malloc(sizeof(t_fdf));
	if (!data)
		return (0);
	initialize(data);
	if (!read_file(argv[1], data))
	{
		write(1, "Invalid file name or the file is empty\n", 39);
		free(data);
		return (0);
	}
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "FDF");
	draw_matrix(data);
	mlx_hook(data->win_ptr, 2, 1L<<0, close, data);
	mlx_loop(data->mlx_ptr);
	clean_matrix(data);
}

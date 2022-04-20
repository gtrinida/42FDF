/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/20 15:42:44 by gtrinida         ###   ########.fr       */
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

int	deal_key(int key, void *data)
{
	(void)data;
	printf("%d", key);
	return (0);
}

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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	draw_matrix(data);
	mlx_key_hook(data->win_ptr, deal_key, NULL);
	mlx_loop(data->mlx_ptr);
	clean_matrix(data);
}

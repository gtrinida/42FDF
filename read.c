/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/27 16:11:58 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_matrix_full(char *line, int *z_line)
{
	int		i;
	char	**numbers;

	numbers = ft_split(line, ' ');
	i = 0;
	while (numbers[i])
	{
		z_line[i] = ft_atoi(numbers[i]);
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

void	read_file_utils(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		get_matrix_full(line, data->z_matrix[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
}

void	get_hight(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;

	line = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!valid(line))
		{
			free(line);
			write(1, "Invalid map\n", 12);
			exit(0);
		}
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	get_width(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		tmp;
	int		error;

	error = 0;
	tmp = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	data->width = ft_wdcounter(line, ' ');
	while (line)
	{
		tmp = ft_wdcounter(line, ' ');
		if (tmp != data->width && !error)
			error = 1;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (error)
		return (0);
	return (1);
}

int	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) < 0
		|| !is_it_empty(file_name))
		return (0);
	if (!get_width(file_name, data))
		return (0);
	get_hight(file_name, data);
	data->z_matrix = ft_calloc_z(data->height, data->width);
	if (!data->z_matrix)
		return (0);
	read_file_utils(file_name, data);
	return (1);
}

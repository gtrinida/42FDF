/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/19 18:34:47 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_width(char *line)
{
	int	i;
	int	flag;
	int	len;

	len = 0;
	flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] >= '0' && line[i + 1] <= '9' && !flag)
		{
			len++;
			flag = 1;
		}
		if (line[i] >= '0' && line[i] <= '9' && !flag)
		{
			len++;
			flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	return (len);
}

void	get_hight(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;

	line = 0;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		data->height++;
		free(line);
	}
	free(line);
	close(fd);
}

void	get_width(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	get_next_line(fd, &line);
	data->width = check_width(line);
	free(line);
	while (get_next_line(fd, &line) > 0)
		free(line);
	if (line)
		free(line);
	close(fd);
}

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

int	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1 || !is_it_empty(file_name))
		return (0);
	get_hight(file_name, data);
	get_width(file_name, data);
	data->z_matrix = ft_calloc_2d(data->height, data->width);
	if (!data->z_matrix)
		return (0);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		get_matrix_full(line, data->z_matrix[i]);
		free(line);
		i++;
	}
	free(line);
	close(fd);
	return (1);
}

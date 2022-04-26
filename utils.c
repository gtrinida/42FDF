/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/26 19:02:17 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_format(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 1] != 'f' && file_name[i - 2] != 'd'
		&& file_name[i - 3] != 'f' && file_name[i - 4] != '.')
		return (0);
	else
		return (1);
}

int	valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == ' '
			|| line[i] == '-' || line[i] == '\n')
			i++;
		else if (line[i] == ',')
		{	
			while ((line[i] != ' ' && line[i]))
				i++;
		}
		else if (line[i])
			return (0);
	}	
	return (1);
}

void	pos_init(t_coordinates *pos)
{
	pos->x = 0;
	pos->x1 = 0;
	pos->y = 0;
	pos->y1 = 0;
}

int	**ft_calloc_2d(int hight, int width)
{
	int	**p;
	int	i;

	i = 0;
	p = ft_calloc(hight, sizeof(int *));
	if (!p)
		return (0);
	while (i < hight)
	{
		p[i] = ft_calloc(width, sizeof(int));
		if (!p[i])
			return (0);
		i++;
	}
	return (p);
}

int	is_it_empty(char *file_name)
{
	int		fd;
	char	*line;
	int		len;

	line = NULL;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	len = ft_strlen(line);
	if (len == 0)
	{
		free(line);
		return (0);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}

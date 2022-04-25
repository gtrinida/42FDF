/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/25 20:26:58 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_wdcounter(const char *str, char separator)
{
	int	i;
	int	finded;
	int	counter;

	i = 0;
	finded = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && finded == 0 && ++counter)
			finded = 1;
		else if (str[i] == separator)
			finded = 0;
		i++;
	}
	return (counter);
}

int valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-' || line[i] == '+'
		|| (line[i] >= '0' && line[i] <= '9'))
			i++;
		else
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

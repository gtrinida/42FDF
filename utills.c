/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/21 16:13:07 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pos_init(t_basic *pos)
{
	pos->x = 0;
	pos->x1 = 0;
	//pos->y = -1;
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
	get_next_line(fd, &line);
	len = ft_strlen(line);
	if (len == 0)
	{
		free(line);
		return (0);
	}
	free(line);
	while (get_next_line(fd, &line) > 0)
		free(line);
	if (line)
		free(line);
	return (1);
}

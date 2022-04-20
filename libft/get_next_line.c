/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:21:28 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/05 14:48:25 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_with_end(char **line)
{
	free(*line);
	*line = 0;
	return (-1);
}

char	*ft_new_line(char **remainder, char **line)
{
	char	*n_pointer;

	n_pointer = 0;
	if (*remainder)
	{
		n_pointer = ft_strchr(*remainder, '\n');
		if (n_pointer)
		{
			*n_pointer = '\0';
			*line = ft_strdup(*remainder);
			ft_strcpy(*remainder, n_pointer + 1);
		}
		else
		{
			*line = ft_strdup(*remainder);
			free(*remainder);
			*remainder = 0;
		}
	}
	else
	{
		*line = malloc(sizeof(char));
		*line[0] = '\0';
	}
	return (n_pointer);
}

int	ft_read(int fd, int *byte_was_read, char *buf)
{
	*byte_was_read = (int) read(fd, buf, BUFFER_SIZE);
	return (*byte_was_read);
}

char	*ft_free_line(char **line, char *buf)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, buf);
	free(temp);
	if (!(*line))
		return (0);
	return (*line);
}

int	get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				byte_was_read;
	char			*n_pointer;
	static char		*remainder;

	byte_was_read = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	n_pointer = ft_new_line(&remainder, line);
	while (!n_pointer && ft_read(fd, &byte_was_read, buf) > 0)
	{
		buf[byte_was_read] = '\0';
		n_pointer = ft_strchr(buf, '\n');
		if (n_pointer)
		{
			*n_pointer = '\0';
			remainder = ft_strdup(n_pointer + 1);
		}
		*line = ft_free_line(line, buf);
		if (!(*line))
			return (-1);
	}
	if (byte_was_read < 0)
		return (ft_free_with_end(line));
	return ((n_pointer && ft_strlen(*line)) || byte_was_read);
}

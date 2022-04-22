/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/22 18:48:48 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"
# include <math.h>

typedef struct s_fdf
{
	int		width;
	int		height;
	int		**z_matrix;
	int		zoom;
	int		color;
	void	*mlx_ptr;
	void	*win_ptr;
}t_fdf;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		z_pos;
	int		z1_pos;	
}t_coordinates;

typedef struct s_matrix
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		zoom;
}t_matrix;

int		read_file(char *file_name, t_fdf *data);
int		**ft_calloc_2d(int n_rows, int n_cols);
int		is_it_empty(char *file_name);
int		draw_matrix(t_fdf *data);
void	pos_init(t_coordinates *pos);
void	zoom(t_coordinates *pos_tmp, t_fdf *data);
void	isometric(t_coordinates *pos, int flag);
void	color(t_coordinates *pos_tmp, t_fdf *data);
void	position(t_coordinates *pos_tmp);

#endif

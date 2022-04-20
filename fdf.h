/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:38:01 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/19 16:15:14 by gtrinida         ###   ########.fr       */
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

typedef struct s_basic
{
	float	x;
	float	y;
	float	x1;
	float	y1;
}t_basic;

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
void	draw_matrix(t_fdf *data);
void	pos_init(t_basic *pos);

#endif

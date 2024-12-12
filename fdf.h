/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:11:28 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/12 15:55:50 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

typedef struct s_pixel
{
	double	z;
	double	x;
	int		y;
	int	color;
}		t_pixel;

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <mlx.h>

int	get_row_col_len(char *file_name, int *col_len, int *row_len);
int	grid_parse(char *file_name, t_pixel ***grid, int *y_len);

#endif

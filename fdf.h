/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:11:28 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/18 13:12:14 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ANGLE 0.52359
# define WIDTH 1800
# define HEIGHT 1500

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <mlx.h>
# include <errno.h>

typedef struct s_pixel
{
	float	z;
	float	x;
	float	y;
	int		active;
	int		color;
}		t_pixel;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_img_info
{
	float	offset_x;
	float	offset_y;
	float	scale_factor;
	float	img_width;
	float	img_height;
	int		grid_x_len;
	int		grid_y_len;
	float	move_x;
	float	move_y;
	float	min_y;
	float	min_x;
	void	*win;
	void	*mlx;
	t_data	img;
	t_pixel	**grid;
}				t_img_info;

int		get_row_col_len(char *file_name, int *col_len, int *row_len);
int		grid_parse(char *file_name, t_pixel ***grid, t_img_info *viewport);
void	draw_image(t_img_info *viewport);
int		create_image(t_img_info *viewport);
int		hex_to_int(char *hex);
void	find_img_dimensions(t_img_info *viewport);
void	iso_convertion(t_img_info *viewport);
int		key_press(int keycode, t_img_info *viewport);
int		handle_close(t_img_info *viewport);

#endif

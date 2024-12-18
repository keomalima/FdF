/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:44 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/18 10:53:43 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_factor(t_img_info *viewport)
{
	float	scale_x;
	float	scale_y;
	float	scale_factor;

	if (!viewport->scale_factor)
	{
		scale_x = (0.8 * WIDTH) / viewport->img_width;
		scale_y = (0.8 * HEIGHT) / viewport->img_height;
		if (scale_x > scale_y)
			scale_factor = scale_y;
		else
			scale_factor = scale_x;
		viewport->scale_factor = scale_factor;
	}
	viewport->offset_x = (WIDTH - (viewport->img_width
		* viewport->scale_factor)) / 2 - (viewport->min_x
		* viewport->scale_factor);
	viewport->offset_y = (HEIGHT - (viewport->img_height
		* viewport->scale_factor)) / 2 - (viewport->min_y
		* viewport->scale_factor);
}

void	find_y_min_max(t_img_info *viewport)
{
	int	y;
	int	x;
	int	max_y;
	int	min_y;

	y = 0;
	max_y = INT_MIN;
	min_y = INT_MAX;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x && viewport->grid[y][x].active > 0)
		{
			if (viewport->grid[y][x].y > max_y)
				max_y = viewport->grid[y][x].y;
			if (viewport->grid[y][x].y < min_y)
				min_y = viewport->grid[y][x].y;
			x++;
		}
		y++;
	}
	viewport->min_y = min_y;
	viewport->img_height = max_y - min_y;
}

void	find_x_min_max(t_img_info *viewport)
{
	int	y;
	int	x;
	int	max_x;
	int	min_x;

	y = 0;
	max_x = INT_MIN;
	min_x = INT_MAX;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x && viewport->grid[y][x].active > 0)
		{
			if (viewport->grid[y][x].x > max_x)
				max_x = viewport->grid[y][x].x;
			if (viewport->grid[y][x].x < min_x)
				min_x = viewport->grid[y][x].x;
			x++;
		}
		y++;
	}
	viewport->min_x = min_x;
	viewport->img_width = max_x - min_x;
}

void	find_img_dimensions(t_img_info *viewport)
{
	if (!viewport->grid)
		return ;
	find_y_min_max(viewport);
	find_x_min_max(viewport);
	scale_factor(viewport);
}

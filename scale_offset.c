/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:44 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/19 08:19:32 by kricci-d         ###   ########.fr       */
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
		scale_x = (0.9 * WIDTH) / viewport->img_width;
		scale_y = (0.9 * HEIGHT) / viewport->img_height;
		if (scale_x > scale_y)
			scale_factor = scale_y;
		else
			scale_factor = scale_x;
		viewport->scale_factor = scale_factor;
	}
	if (viewport->min_x > 0)
		viewport->min_x = 0;
	if (viewport->min_y > 0)
		viewport->min_y = 0;
	viewport->offset_x = (WIDTH - (viewport->img_width
				* viewport->scale_factor)) / 2 - viewport->min_x
		* viewport->scale_factor;
	viewport->offset_y = (HEIGHT - (viewport->img_height
				* viewport->scale_factor)) / 2 - viewport->min_y
		* viewport->scale_factor;
}

void	find_y_min_max(t_img_info *viewport)
{
	int		y;
	int		x;

	y = 0;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x && viewport->grid[y][x].active > 0)
		{
			if (viewport->grid[y][x].y > viewport->max_y)
				viewport->max_y = viewport->grid[y][x].y;
			if (viewport->grid[y][x].y < viewport->min_y)
				viewport->min_y = viewport->grid[y][x].y;
			x++;
		}
		y++;
	}
	viewport->img_height = viewport->max_y - viewport->min_y;
}

void	find_x_min_max(t_img_info *viewport)
{
	int		y;
	int		x;

	y = 0;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x && viewport->grid[y][x].active > 0)
		{
			if (viewport->grid[y][x].x > viewport->max_x)
				viewport->max_x = viewport->grid[y][x].x;
			if (viewport->grid[y][x].x < viewport->min_x)
				viewport->min_x = viewport->grid[y][x].x;
			x++;
		}
		y++;
	}
	viewport->img_width = viewport->max_x - viewport->min_x;
}

void	initial_map_info(t_img_info *viewport)
{
	viewport->max_x = viewport->grid[0][0].x;
	viewport->min_x = viewport->grid[0][0].x;
	viewport->max_y = viewport->grid[0][0].y;
	viewport->min_y = viewport->grid[0][0].y;
}

void	find_img_dimensions(t_img_info *viewport)
{
	if (!viewport->grid)
		return ;
	initial_map_info(viewport);
	find_y_min_max(viewport);
	find_x_min_max(viewport);
	scale_factor(viewport);
}

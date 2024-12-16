/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:44 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 14:26:20 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_y_min_max(t_img_info *viewport)
{
	int	y;
	int	x;
	int	max_y;
	int min_y;

	y = 0;
	max_y = INT_MIN;
	min_y = INT_MAX;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x)
		{
			if (viewport->grid[y][x].y > max_y)
				max_y = viewport->grid[y][x].y;
			if (viewport->grid[y][x].y < min_y)
				min_y = viewport->grid[y][x].y;
			x++;
		}
		y++;
	}
	viewport->img_height = abs(max_y - min_y);
}

void	find_x_min_max(t_img_info *viewport)
{
	int	y;
	int	x;
	int	max_x;
	int min_x;

	y = 0;
	max_x = INT_MIN;
	min_x = INT_MAX;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x)
		{
			if (viewport->grid[y][x].x > max_x)
				max_x = viewport->grid[y][x].x;
			if (viewport->grid[y][x].x < min_x)
				min_x = viewport->grid[y][x].x;
			x++;
		}
		y++;
	}
	viewport->img_width = abs(max_x - min_x);
}

void	find_img_dimensions(t_img_info *viewport)
{
	if (!viewport->grid)
		return;
	find_y_min_max(viewport);
	find_x_min_max(viewport);
	viewport->offset_x = (WIDTH - viewport->img_width) / 2;
	viewport->offset_y = (HEIGHT - viewport->img_height) / 2;
}

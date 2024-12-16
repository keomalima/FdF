/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:22:59 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/16 22:14:33 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_trans(t_img_info *viewport, int y, int x)
{
	float	z;

	z = viewport->grid[y][x].z;
	//z = (z - viewport->min_z) / (viewport->max_z - viewport->min_z);
	viewport->grid[y][x].x = (x * cos(ANGLE) + y * cos(ANGLE + 2) + z * cos(ANGLE - 2));
	viewport->grid[y][x].y = (x * sin(ANGLE) + y * sin(ANGLE + 2) + z * sin(ANGLE - 2));
}

void	find_max_z(t_img_info *viewport)
{
	int y;
	int x;
	int max_z;
	int	min_z;

	y = 0;
	max_z = INT_MIN;
	min_z = INT_MAX;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x)
		{
			if (viewport->grid[y][x].z > max_z)
				max_z = viewport->grid[y][x].z;
			if (viewport->grid[y][x].z < min_z)
				min_z = viewport->grid[y][x].z;
			x++;
		}
		y++;
	}
	viewport->min_z = min_z;
	viewport->max_z = max_z;
}

void	iso_convertion(t_img_info *viewport)
{
	int	y;
	int	x;

	find_max_z(viewport);
	y = 0;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x)
		{
			iso_trans(viewport, y, x);
			x++;
		}
		y++;
	}
}
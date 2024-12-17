/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:22:59 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/17 17:56:48 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void find_gap_vertical(t_img_info *viewport, int *gap, int *count)
{
	int	y;
	int	x;

	y = 0;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len - 1 > x && viewport->grid[y][x + 1].active)
		{
			if (viewport->grid[y + 1] && viewport->grid[y + 1][x].active)
			{
				if (viewport->grid[y + 1][x].z != viewport->grid[y][x].z)
				{
					*gap += abs(viewport->grid[y + 1][x].z - viewport->grid[y][x].z);
					(*count)++;
				}
			}
			x++;
		}
		y++;
	}
}

void find_gap_horizontal(t_img_info *viewport, int *gap, int *count)
{
	int y;
	int x;

	y = 0;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len - 1 > x && viewport->grid[y][x + 1].active > 0)
		{
			if (viewport->grid[y][x + 1].z != viewport->grid[y][x].z)
			{
				*gap += abs(viewport->grid[y][x + 1].z - viewport->grid[y][x].z);
				(*count)++;
			}
			x++;
		}
		y++;
	}
}

void	iso_trans(t_img_info *viewport, int y, int x, int z_factor)
{
	float	z;
	static	i;

	if (viewport->grid[y][x].z == 0 || z_factor == 0)
		z = viewport->grid[y][x].z;
	else
		z = viewport->grid[y][x].z  / z_factor;
	viewport->grid[y][x].x = (x * cos(ANGLE) + y * cos(ANGLE + 2) + z * cos(ANGLE - 2));
	viewport->grid[y][x].y = (x * sin(ANGLE) + y * sin(ANGLE + 2) + z * sin(ANGLE - 2));
}

void	iso_convertion(t_img_info *viewport)
{
	int	y;
	int	x;
	int	gap;
	int	count;
	int	z_factor;

	count = 0;
	gap = 0;
	y = 0;
	find_gap_horizontal(viewport, &gap, &count);
	find_gap_vertical(viewport, &gap, &count);
	z_factor = 0;
	if (count != 0 && gap != 0)
		z_factor = gap/count;
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len > x)
		{
			iso_trans(viewport, y, x, z_factor);
			x++;
		}
		y++;
	}
}

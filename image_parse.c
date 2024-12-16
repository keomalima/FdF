/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:15:16 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 09:17:12 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void slope_bigger_than_one(t_data *img, int dx, int dy, t_pixel init)
{
	int	i;
	int	p;

	p = 2 * abs(dx) - abs(dy);
	i = 0;
	while (abs(dy) > i)
	{
		init.y += (dy > 0) ? 1 : -1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			init.x += (dx > 0) ? 1 : -1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		my_mlx_pixel_put(img, init.x, init.y, 0xFF0000);
		i++;
	}
}

void slope_less_than_one(t_data *img, int dx, int dy, t_pixel init)
{
	int	i;
	int	p;

	p = 2 * abs(dy) - abs(dx);
	i = 0;
	while (abs(dx) > i)
	{
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			init.y += (dy > 0) ? 1 : -1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		init.x += (dx > 0) ? 1 : -1;
		my_mlx_pixel_put(img, init.x, init.y, 0xFF0000);
		i++;
	}
}

void	slope_decide(t_data *img, t_pixel init, t_pixel end)
{
	int	dx;
	int	dy;

	dx =  end.x - init.x;
	dy = end.y - init.y;
	if (abs(dx) > abs(dy))
		slope_less_than_one(img, dx, dy, init);
	else
		slope_bigger_than_one(img, dx, dy, init);
}

void	create_image(t_data *img, t_pixel **grid, int x_len)
{
	int		x;
	int		y;

	if (!grid || x_len <= 0)
		return;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (x_len - 1 > x)
		{
			slope_decide(img, grid[y][x], grid[y][x + 1]);
			if (grid[y + 1])
				slope_decide(img, grid[y][x], grid[y + 1][x]);
			x++;
		}
		if (grid[y + 1])
			slope_decide(img, grid[y][x], grid[y + 1][x]);
		y++;
	}
}

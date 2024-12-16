/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:15:16 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 17:23:16 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img_info *viewport, int x, int y, int color)
{
	char	*dst;

	if (!color)
		color = 0xFF0000;
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		//printf("(%d, %d) ", y, x);
		dst = viewport->img.addr + (y * viewport->img.line_length
				+ x * (viewport->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	slope_bigger_than_one(t_img_info *viewport, int dx, int dy, t_pixel init)
{
	int	i;
	int	p;

	p = 2 * abs(dx) - abs(dy);
	i = 0;
	while (abs(dy) >= i)
	{
		my_mlx_pixel_put(viewport, init.x, init.y, init.color);
		init.y += (dy > 0) ? 1 : -1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			init.x += (dx > 0) ? 1 : -1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		i++;
	}
}

void	slope_less_than_one(t_img_info *viewport, int dx, int dy, t_pixel init)
{
	int	i;
	int	p;

	p = 2 * abs(dy) - abs(dx);
	i = 0;
	while (abs(dx) >= i)
	{
		my_mlx_pixel_put(viewport, init.x, init.y, init.color);
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			init.y += (dy > 0) ? 1 : -1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		init.x += (dx > 0) ? 1 : -1;
		i++;
	}
}

void	slope_decide(t_img_info *viewport, t_pixel init, t_pixel end)
{
	int	dx;
	int	dy;

	dx = end.x - init.x;
	dy = end.y - init.y;
	if (abs(dx) > abs(dy))
		slope_less_than_one(viewport, dx, dy, init);
	else
		slope_bigger_than_one(viewport, dx, dy, init);
	printf("\n");
}

void	create_image(t_img_info *viewport)
{
	int	x;
	int	y;

	if (!viewport->grid)
		return ;
	y = 0;
	find_img_dimensions(viewport);
	printf("%d\n", viewport->scale_factor);
	convert_iso(viewport);
	while (viewport->grid[y])
	{
		x = 0;
		while (viewport->grid_x_len - 1 > x)
		{
			slope_decide(viewport, viewport->grid[y][x], viewport->grid[y][x + 1]);
			if (viewport->grid[y + 1])
				slope_decide(viewport, viewport->grid[y][x], viewport->grid[y + 1][x]);
			x++;
		}
		if (viewport->grid[y + 1])
			slope_decide(viewport, viewport->grid[y][x], viewport->grid[y + 1][x]);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:20:29 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/18 09:01:28 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_press(int keycode, t_img_info *viewport)
{
	int	i;

	if (keycode == 65307)
	{
		if (viewport->grid)
		{
			i = 0;
			while (viewport->grid[i])
				free(viewport->grid[i++]);
			free(viewport->grid);
		}
		mlx_destroy_image(viewport->mlx, viewport->img.img);
		mlx_destroy_window(viewport->mlx, viewport->win);
		mlx_destroy_display(viewport->mlx);
		free(viewport->mlx);
		viewport->mlx = NULL;
		exit(0);
	}
	return (0);
}

int	handle_close(t_img_info *viewport)
{
	int	i;

	if (viewport->grid)
	{
		i = 0;
		while (viewport->grid[i])
			free(viewport->grid[i++]);
		free(viewport->grid);
	}
	mlx_destroy_image(viewport->mlx, viewport->img.img);
	mlx_destroy_window(viewport->mlx, viewport->win);
	mlx_destroy_display(viewport->mlx);
	free(viewport->mlx);
	viewport->mlx = NULL;
	exit(0);
	return (0);
}

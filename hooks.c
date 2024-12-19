/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:20:29 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/19 09:22:33 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_map_bonus(int keycode, t_img_info *viewport)
{
	mlx_destroy_image(viewport->mlx, viewport->img.img);
	viewport->img.img = NULL;
	if (keycode == 65451)
		viewport->scale_factor *= 2;
	if (keycode == 65453)
		viewport->scale_factor /= 2;
	if (keycode == 100)
		viewport->move_x += 30;
	if (keycode == 97)
		viewport->move_x -= 30;
	if (keycode == 119)
		viewport->move_y -= 30;
	if (keycode == 115)
		viewport->move_y += 30;
	if (keycode == 122 || keycode == 120)
	{
		if (keycode == 120 && (viewport->z_factor_bonus + 1.1) < 20.0)
			viewport->z_factor_bonus += 1.1;
		if (keycode == 122 && (viewport->z_factor_bonus - 1.1) >= -20.0)
				viewport->z_factor_bonus -= 1.1;
		iso_convertion(viewport);
	}
	create_image(viewport);
	return (0);
}

int	close_press(t_img_info *viewport)
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

int	key_press(int keycode, t_img_info *viewport)
{
	if (keycode == 65307)
		close_press(viewport);
	if (keycode == 65451 || keycode == 65453)
		ft_map_bonus(keycode, viewport);
	else if (keycode == 100 || keycode == 97)
		ft_map_bonus(keycode, viewport);
	else if (keycode == 119 || keycode == 115)
		ft_map_bonus(keycode, viewport);
	else if (keycode == 120 || keycode == 122)
		ft_map_bonus(keycode, viewport);
	return (0);
}

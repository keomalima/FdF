/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:52:18 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 14:41:44 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	minilibx_init(t_img_info *viewport)
{
	void	*mlx;
	void	*win;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	viewport->mlx = mlx;
	viewport->win = win;
	viewport->img = img;
	create_image(viewport);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

int	ft_fdf(char *file_name)
{
	int			i;
	t_pixel		**grid;
	t_img_info	viewport;

	grid = NULL;
	if (grid_parse(file_name, &grid, &viewport) == 1)
		return (1);
	minilibx_init(&viewport);
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_fdf(av[1]) == -1)
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:52:18 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/18 13:12:40 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_image(t_img_info *viewport)
{
	t_data	img;

	img.img = mlx_new_image(viewport->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	if (!img.img || !img.addr)
		return (1);
	viewport->img = img;
	draw_image(viewport);
	mlx_put_image_to_window(viewport->mlx, viewport->win, img.img, 0, 0);
}

int	minilibx_config(t_img_info *viewport)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF");
	if (!win)
		return (1);
	viewport->mlx = mlx;
	viewport->win = win;
	viewport->move_x = 0;
	viewport->move_y = 0;
	viewport->scale_factor = 0;
	create_image(viewport);
	mlx_hook(win, 17, 0, handle_close, viewport);
	mlx_hook(win, 2, 1, key_press, viewport);
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
	{
		errno = ENOMEM;
		perror("Parsing error");
		return (1);
	}
	if (minilibx_config(&viewport) == 1)
	{
		errno = ENOMEM;
		perror("Minilibx error");
		return (1);
	}
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
	else
	{
		errno = EINVAL;
		if (ac == 1)
			perror("Too few arguments");
		else
			perror("Too many arguments");
		return (1);
	}
	return (0);
}

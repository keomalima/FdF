/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:52:18 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/12 15:43:00 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	minilibx(t_pixel ***grid, int y_len)
{
	void	*mlx;
	void	*win;
	int		i;
	int		j;
	(void)grid;
	(void)y_len;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 1200, 800, "FdF");
	i = 0;
	while ((*grid)[i])
	{
		j = 0;
		while (y_len > j)
		{
			mlx_pixel_put(mlx, win, grid[i][j]->y * 10, grid[i][j]->x * 10, (*grid)[i][j].color ? (*grid)[i][j].color : 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_loop(mlx);
	return (0);
}

int	ft_fdf(char *file_name)
{
	int		i;
	int		y_len;
	t_pixel **grid;

	grid = NULL;
	if (grid_parse(file_name, &grid, &y_len) == 1)
		return (1);
	//minilibx(&grid, y_len);
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

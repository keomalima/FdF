/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:52:18 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/12 14:25:25 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	grid_parse(char *file_name, t_pixel ***grid)
{
	int	x_len;
	int	y_len;
	int	fd;

	if (get_row_col_len(file_name, &x_len, &y_len) == 1)
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	if (ft_grid_allocate(fd, grid, x_len, y_len) == 1)
	{
		close (fd);
		return (1);
	}
	close(fd);
	return (0);
}
int	ft_fdf(char *file_name)
{
	int i;
	t_pixel **grid;

	grid = NULL;
	if (grid_parse(file_name, &grid) == 1)
		return (1);
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

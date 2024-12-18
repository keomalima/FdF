/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:21:01 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/18 10:02:24 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_parse(t_pixel **grid, char **tab, int x_len)
{
	char	*pixel;
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (tab[i] && x_len > i)
	{
		(*grid)[x].active = 0;
		if (ft_isdigit(tab[i][0]) || tab[i][0] == '-')
		{
			(*grid)[x].z = ft_atoi(tab[i]);
			(*grid)[x].active = 1;
			pixel = ft_strchr(tab[i], ',');
			if (pixel)
				(*grid)[x].color = hex_to_int(pixel);
			else
				(*grid)[x].color = 0;
			x++;
		}
		free(tab[i]);
		i++;
	}
}

int	y_parse(t_pixel **grid, int fd, int x_len)
{
	int		y;
	char	*line;
	char	**tab;

	y = 0;
	while (grid[y])
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tab = ft_split(line, 32);
		free(line);
		if (!tab)
		{
			while (y > 0)
				free(grid[--y]);
			free(grid);
			return (1);
		}
		x_parse(&grid[y], tab, x_len);
		free(tab);
		y++;
	}
	return (0);
}

int	ft_grid_allocate(int fd, t_pixel ***grid, int x_len, int y_len)
{
	int		y;

	*grid = malloc (sizeof (t_pixel *) * (y_len + 1));
	if (!*grid)
		return (1);
	y = 0;
	while (y_len > y)
	{
		(*grid)[y] = malloc (sizeof (t_pixel) * x_len);
		if (!(*grid)[y])
		{
			while (y > 0)
				free((*grid)[--y]);
			free(*grid);
			return (1);
		}
		y++;
	}
	(*grid)[y_len] = NULL;
	if (y_parse(*grid, fd, x_len) == 1)
		return (1);
	return (0);
}

int	grid_parse(char *file_name, t_pixel ***grid, t_img_info *viewport)
{
	int	y_len;
	int	x_len;
	int	fd;

	if (get_row_col_len(file_name, &x_len, &y_len) == 1)
		return (1);
	if (y_len == 0 || x_len == 0)
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
	viewport->grid_x_len = x_len;
	viewport->grid_y_len = y_len;
	viewport->grid = *grid;
	iso_convertion(viewport);
	return (0);
}

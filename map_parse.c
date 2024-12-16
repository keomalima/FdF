/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:21:01 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 09:08:02 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_trans(t_pixel *pixel, int y, int x, int z)
{
	pixel->x = round((x * cos(ANGLE) + y * cos(ANGLE + 2) + z * cos(ANGLE - 2)) * 25);
	pixel->y = round((x * sin(ANGLE) + y * sin(ANGLE + 2) + z * sin(ANGLE - 2)) * 25);
}

int	hex_to_int(char *hex)
{
	int		i;
	int		j;
	int		color;
	char	*hex_base;

	hex_base = "0123456789ABCDEF";
	color = 0;
	if (!hex || ft_strlen(hex) < 3)
		return (0);
	i = 3;
	while (hex[i])
	{
		if (hex[i] >= 'a' && hex[i] <= 'f')
			hex[i] = ft_toupper(hex[i]);
		j = 0;
		while (hex_base[j] && hex[i] != hex_base[j])
			j++;
		if (!hex_base[j])
			return (0);
		color = color * 16 + j;
		i++;
	}
	return (color);
}

void	x_parse(t_pixel **grid, char **tab, int y)
{
	char	*pixel;
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[i][0]) || tab[i][0] == '-')
		{
			(*grid)[x].z = ft_atoi(tab[i]);
			iso_trans (&(*grid)[x], y, x, ft_atoi(tab[i]));
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

int	y_parse(t_pixel **grid, int fd)
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
		x_parse(&grid[y], tab, y);
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
	if (y_parse(*grid, fd) == 1)
		return (1);
	return (0);
}

int	grid_parse(char *file_name, t_pixel ***grid, int *x_len)
{
	int	y_len;
	int	fd;

	if (get_row_col_len(file_name, x_len, &y_len) == 1)
		return (1);
	if (y_len == 0 || *x_len == 0)
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	if (ft_grid_allocate(fd, grid, *x_len, y_len) == 1)
	{
		close (fd);
		return (1);
	}
	close(fd);
	return (0);
}

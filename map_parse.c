/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:21:01 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/12 14:10:57 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	populate_pixel_data(t_pixel **grid, char **tab)
{
	char	*pixel;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[i][0]) || tab[i][0] == '-')
		{
			(*grid)[j].z = ft_atoi(tab[i]);
			pixel = ft_strchr(tab[i], ',');
			if (pixel)
				(*grid)[j].color = hex_to_int(pixel);
			else
				(*grid)[j].color = 0;
			j++;
		}
		free(tab[i]);
		i++;
	}
}

int	pixel_parse(t_pixel ***grid, int fd)
{
	int		i;
	char	*line;
	char	**tab;

	i = 0;
	while ((*grid)[i])
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tab = ft_split(line, 32);
		free(line);
		if (!tab)
		{
			while (i > 0)
				free((*grid)[--i]);
			free(*grid);
			return (1);
		}
		populate_pixel_data(&(*grid)[i], tab);
		free(tab);
		i++;
	}
	return (0);
}

int	ft_grid_allocate(int fd, t_pixel ***grid, int x_len, int y_len)
{
	int		i;

	*grid = malloc (sizeof (t_pixel *) * (x_len + 1));
	if (!*grid)
		return (1);
	i = 0;
	while (x_len > i)
	{
		(*grid)[i] = malloc (sizeof (t_pixel) * y_len);
		if (!(*grid)[i])
		{
			while (i > 0)
				free((*grid)[--i]);
			free(*grid);
			return (1);
		}
		i++;
	}
	(*grid)[x_len] = NULL;
	if (pixel_parse(grid, fd) == 1)
		return (1);
	return (0);
}
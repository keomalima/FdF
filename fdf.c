/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:52:18 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/11 17:33:21 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_line_len(char *line)
{
	char	**tab;
	int		i;
	int		len;

	tab = ft_split(line, 32);
	if (!tab)
		return (0);
	i = 0;
	len = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[i][0]) || tab[i][0] == '-')
			len++;
		free(tab[i++]);
	}
	free(tab);
	return (len);
}

void	ft_get_map(int fd, char **grid, int *column_len, int *line_len)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	if (line)
		(*line_len) = ft_line_len(line);
	while (line)
	{
		if (line && (ft_isdigit(line[0]) || line[0] == '-'))
			(*column_len)++;
		temp = *grid;
		*grid = ft_strjoin(*grid, line);
		free(line);
		if (!*grid)
			return (free(temp));
		free(temp);
		line = get_next_line(fd);
	}
}

void	ft_grid_parse(int fd)
{
	char	**grid;
	int		column_len;
	int		line_len;
	int		i;

	column_len = 0;
	line_len = 0;
	grid = calloc(1, 1);
	if (!grid)
		return ;
	ft_get_map(fd, grid, &column_len, &line_len);
	grid = malloc (sizeof (t_pixel *) * line_len);
	if (!grid)
		return ;
	i = 0;
	while (line_len > i)
	{
		grid[i] = malloc (sizeof (t_list) * column_len);
		if (!grid[i])
			return (clean_grid(grid));
	}
	// populate grid and treat it
}


int	main(int ac, char **av)
{
	int	fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (!fd)
			return (1);
		ft_grid_parse(fd);
	}
	return (0);
}

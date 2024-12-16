/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:20:49 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 09:20:49 by kricci-d         ###   ########.fr       */
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

int	map_x_len(char *read, int *x_len)
{
	int		i;
	char	**tab;

	if (read)
	{
		tab = ft_split(read, 32);
		if (!tab)
			return (1);
		i = 0;
		while (tab[i])
		{
			if (ft_isdigit(tab[i][0]) || tab[i][0] == '-')
				(*x_len)++;
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

int	map_y_len(int fd, int *x_len, int *y_len)
{
	char	*read;
	int		i;

	read = get_next_line(fd);
	if (map_x_len(read, x_len) == 1)
	{
		free(read);
		return (1);
	}
	while (read)
	{
		i = 0;
		while (read[i])
		{
			if (ft_isalnum(read[i]))
			{
				(*y_len)++;
				break ;
			}
			i++;
		}
		free(read);
		read = get_next_line(fd);
	}
	return (0);
}

int	get_row_col_len(char *file_name, int *x_len, int *y_len)
{
	int	fd_map_len;

	*x_len = 0;
	*y_len = 0;
	fd_map_len = open(file_name, O_RDONLY);
	if (fd_map_len < 0)
		return (1);
	if (map_y_len(fd_map_len, x_len, y_len) == 1)
	{
		close(fd_map_len);
		return (1);
	}
	close (fd_map_len);
	return (0);
}

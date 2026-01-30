/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/01/30 16:09:27 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**map_copy(t_map *map)
{
	int		i;
	char	**map_copy;

	map_copy = ft_calloc(map->y_len + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < map->y_len)
	{
		map_copy[i] = ft_strdup(map->grid[i]);
		if (!map_copy[i])
		{
			ft_freearr((void *)map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	floodfill(t_map *map, char **map_copy, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->x_len || y >= map->y_len)
		return (FAILURE);
	if (map_copy[y][x] == '\0' || map_copy[y][x] == ' ')
		return (FAILURE);
	if (map_copy[y][x] == WALL || map_copy[y][x] == 'X')
		return (SUCCESS);
	map_copy[y][x] = 'X';
	if (floodfill(map, map_copy, x + 1, y))
		return (FAILURE);
	if (floodfill(map, map_copy, x - 1, y))
		return (FAILURE);
	if (floodfill(map, map_copy, x, y + 1))
		return (FAILURE);
	if (floodfill(map, map_copy, x, y - 1))
		return (FAILURE);
	return (SUCCESS);
}

int	validate_map(t_map *map)
{
	int		x;
	int		y;
	char	**copy;
	int		result;

	result = 0;
	copy = map_copy(map);
	if (!copy)
		return (FAILURE);
	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			if (copy[y][x] && ft_strchr("NSEW", copy[y][x]))
			{
				result = floodfill(map, copy, x, y);
				return (ft_freearr((void *)copy), result);
			}
			x++;
		}
		y++;
	}
	return (result);
}

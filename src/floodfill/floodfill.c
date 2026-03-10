/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/03/10 13:08:38 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_map(t_map *map)
{
	t_vars	v;

	v.y = 0;
	v.result = 0;
	v.copy = map_copy(map);
	if (!v.copy)
		return (FAILURE);
	while (v.y < map->y_len)
	{
		v.x = 0;
		while (v.x < map->x_len)
		{
			if (v.copy[v.y][v.x] && ft_strchr("NSEW", v.copy[v.y][v.x]))
			{
				map->player_x = v.x;
				map->player_y = v.y;
				map->orient = v.copy[v.y][v.x];
				v.result = floodfill(map, v.copy, v.x, v.y);
				return (ft_freearr((void *)v.copy), v.result);
			}
			v.x++;
		}
		v.y++;
	}
	return (ft_freearr((void *)v.copy), v.result);
}

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
	printf("------------------MAP_COPY----------------\n");
	i = 0;
	while (i < map->y_len)
		printf("%s\n", map_copy[i++]);
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

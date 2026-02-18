/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:24 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/18 15:56:01 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	map_setup(t_map *map)
{
	map_dimensions(map);
	map->grid = init_grid(map);
	if (!map->grid)
		ft_exit_errc("Grid allocation failed", (void *)&map, 'm');
	read_map_again(map);
	if (one_player(map))
		ft_exit_errc("Game is only one player", (void *)&map, 'p');
	if (is_valid_char(map) == FAILURE)
		ft_exit_errc("Invalid char in map", (void *)&map, 'p');
	if (validate_map(map))
		ft_exit_errc("floodfill failed", (void *)&map, 'f');
}

void	parse_map_first_line(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (i == 0 && frst_last(map->line))
		ft_exit_errc("Invalid map setup", (void *)&map, 'm');
		// ft_exit_errc("Invalid first map row", (void *)&map, 'm');
	while (map->line[j] && map->line[j] != '\n')
	{
		map->grid[i][j] = map->line[j];
		j++;
	}
	while (j < map->x_len)
	{
		map->grid[i][j] = ' ';
		j++;
	}
	map->grid[i][j] = '\0';
	ft_safefree((void *)&map->line);
	i++;
	create_grid(map, i, j);
}

void	create_grid(t_map *map, int i, int j)
{
	while ((i < map->y_len) && (map->line = get_next_line(map->fd)))
	{
		j = 0;
		while (map->line[j] && map->line[j] != '\n')
		{
			map->grid[i][j] = map->line[j];
			j++;
		}
		while (j < map->x_len)
			map->grid[i][j++] = ' ';
		map->grid[i][j] = '\0';
		i++;
		ft_safefree((void *)&map->line);
	}
}

bool	frst_last(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != WALL)
			return (true);
		i++;
	}
	return (false);
}

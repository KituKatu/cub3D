/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:24 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/02 13:01:50 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Your program must take as a first argument a scene description file with the .cub extension.
    ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
    1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
    The map must be closed/surrounded by walls, if not the program must return an error.
    ◦ Except for the map content, each type of element can be separated by one or
    more empty lines.
    ◦ Except for the map content which always has to be the last, each type of
    element can be set in any order in the file.
    ◦ Except for the map, each type of information from an element can be separated
    by one or more spaces.
    ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
    map and are up to you to handle. You must be able to parse any kind of map,
    as long as it respects the rules of the map.
*/

// TODO: Read map in 3:
// 1) paths specified for the textures (?) in MLX
// 2) colour codes for Ceiling and Floor
// 3) map with validations
//      - surrounded by walls --> whitespaces can lead and in between 
//      - instances of player and orientation
//      - whitespaces have valid paths --> flood fill 

void	map_setup(t_map *map)
{
	map_dimensions(map);
	map->grid = init_grid(map);
	if (!map->grid)
		ft_exit_errc("Grid allocation failed", (void *)&map, 'm');
	read_map_again(map);
	if (one_player(map))
		ft_exit_errc("Game is only one player", (void *)&map, 'p');
	if (validate_map(map))
		ft_exit_errc("floodfill failed", (void *)&map, 'f');
}

void	parse_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (i == 0 && frst_last(map->line))
		ft_exit_errc("Invalid first map row", (void *)&map, 'm');
	while (map->line[j] && map->line[j] != '\n')
	{
		map->grid[i][j] = map->line[j];
		j++;
	}
	while (j < map->x_len)
		map->grid[i][j++] = ' ';
	map->grid[i][j] = '\0';
	ft_safefree((void *)&map->line);
	i++;
	create_grid(map, i, j);
	// Tester
	// i = 0;
	// while (i < map->y_len)
	// {
	// 	printf("%s\n", map->grid[i]);
	// 	i++;
	// }
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:24 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/23 14:29:57 by jmcgrane         ###   ########.fr       */
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

t_map	*init_map(char *mapname)
{
	char	*map_path;
	t_map	*map;

	if (dot_cub(mapname))
		ft_exit_error("Wrong file extention");
	map_path = ft_strjoin("./maps/", mapname);
	if (!mapname)
		return (FAILURE); 
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_safefree(&map_path);
		return (FAILURE);
	}
	if (read_map(map_path, map))
	{
		ft_safefree(&map_path);
		ft_exit_errc("Can't read map", &map, 'm');
	}
	ft_safefree(&map_path);
	return (map);
}


bool val_flmaprow(char *line)
{
	int i;
	
	i = 0; 
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != WALL)
			return (true);
		i++;
	}
	return (false);
}

/*we need to parse in 1 go and save to temp buffer 
	if we want to 'remember our place in the map' 
	so I suggest:
	 - reading into buffer
	 - maybe ft_splitting,
	 - calc max length, 
	 - then realloccing / appending the short strings  
*/
void	parse_map(t_map *map, char *line)
{
	char	**grid;
	int i;

	i = 0;
	while (line = get_next_line(map->fd))
	{
		if (map->x_len < ft_strlen(line))
			map->x_len = ft_strlen(line);
		if (!map->mapline && line)
		{
			if (val_flmaprow(line))
				ft_exit_errc("Error upper walls", &map, 'm');
			map->grid[i] = ft_strdup(line);
			if (!map->grid[i])
				ft_exit_errc("Error dup mapline", &map, 'm');
		}
		while(line)
		{
			if (empty_line(line))
				ft_exit_errc("Obstructed map", &map, 'm');
			ft_strjoin(map->mapline, line);
		}
		//check if at EOF --> otherwise, broken map
		if ()
		i++;
	}
	map->y_len = i; 

	// map->grid = init_grid(map, line);
	// if (!map->grid)
	// 	ft_exit_errc("Grid failed to init", &map, 'm');
}

int	read_map(char *mapname, t_map *map)
{
	char	*line;

	map->fd = open(mapname, O_RDONLY);
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	//needs while loop until EOF 
	while(line = get_next_line(map->fd))
	{
		if (empty_line(line))
		{
			ft_safefree(&line);
			continue;
		}
		if (parse_identifier(line, map) == 1)
		{
			parse_map(map, line);
		}
		ft_safefree(line);
	}
	close(map->fd);
	return (SUCCESS);
}



char	**init_grid(t_map *map, char *line)
{
	int		i;
	char	*line;
	char	**grid;

	i = 0;
	grid = calloc(map->y_len + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	while()
	{
		//I need to initlize all strings with map->x_len
	}
	return (grid);
}

void	map_dimensions(t_map *map, char *line)
{
	int	height;
	int	width;
	int	curr_width;

	height = 1;
	width = ft_strlen(line);
	while (line = get_next_line(map->fd))
	{
		curr_width = ft_strlen(line);
		if (curr_width > width)
			width = curr_width;
		ft_safefree(line);
		height++;
	}
	map->x_len = width;
	map->y_len = height;
}




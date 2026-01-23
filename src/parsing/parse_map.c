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


// int val_id_values(char *mapline)
// {
//     int i;
//     char *signstr;

//     i = 0;
//     signstr = "NOSOWEEAFLCE";
//     while (signstr[i])
//     {
//         if (ft_strchr(mapline, signstr[i]))
//         {
//             if (val_textpath(mapline, &signstr[i]))
//                 ft_exit_errc("Wrong values", mapline);
            
//         }
//         i += 2;
//     }
//     return (SUCCESS);
// }

// keep searching for identifiers and validating
// until we can find and parse whole map
// bool val_mapline(char *mapline)
// {
//     if (!mapline)
        
//     val_id_values(mapline, );

//     return (SUCCESS);
// }

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
		ft_exit_errc("Can't read map", &map);
	}
	ft_safefree(&map_path);
	return (map);
}

int	read_map(char *mapname, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		ft_exit_errc("Error opening file", NULL);
	//needs while loop until EOF 
	while(line = get_next_line(fd))
	{
		if (empty_line(line))
		{
			ft_safefree(&line);
			continue;
		}
		if(parse_identifier(line, map) == 1)
		{
			parse_map(map, line, fd);
		}
		free(line);
	}
	// if (val_mapline(ln))
	//     ft_exit_errc("Map invalid", (void **)&ln);
	close(fd);
	return (SUCCESS);
}

void	parse_map(t_map *map, char *line, int fd)
{
	map_dimensions(map, line, fd);
	
}

void	map_dimensions(t_map *map, char *line, int fd)
{
	
}




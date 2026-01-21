/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:24 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/21 15:45:29 by jmcgrane         ###   ########.fr       */
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

void val_colval(char *mapline, char *sign)
{
    if (mapline[0] == sign[0] && mapline[1] == sign[1])
    {
        
    }

}

int val_id_values(char *mapline)
{
    int i;
    char *signstr;
    char *

    i = 0;
    signstr = "NOSOWEEAFLCE";
    while (signstr[i])
    {
        if(i >= 0 && i <= 6)
        {
            ft_strchr(mapline, signstr[i]);
            if (ft_strchr(mapline, signstr[i]))
            {
                if (val_textpath(mapline, &signstr[i]))
                    ft_exit_errc("Wrong values", mapline);
                
            }
        }
        else if (i == 8 || i == 10)
        {

        }
        i += 2;
    }
    return (SUCCESS);
}

// keep searching for identifiers and validating
// until we can find and parse whole map
bool val_mapline(char *mapline)
{
    if (!mapline)
        return()
    val_id_values(mapline, );

    return (SUCCESS);
}



//do we want to validate as we read or do we want to load and then reiterate to validate?
// 
int read_map(char *mapname)
{
    int fd;
    char *ln;
    t_map *map;

    fd = open(mapname, O_RDONLY);
    if (fd < 0)
        ft_exit_errc("Error opening file", NULL);
    map = ft_calloc(1, sizeof(t_map));
    if (!map)
        return (close(fd), FAILURE);
    //needs while loop until EOF 
    
    ln = get_next_line(fd);
    if (val_mapline(ln))
        ft_exit_errc("Map invalid", (void **)&ln);
    close(fd);
    return (SUCCESS);
}







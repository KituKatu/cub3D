/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:13:00 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/16 16:54:55 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
/*
- The management of your window must remain smooth: changing to another window, minimizing, etc.
- Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West
- Your program must be able to set the floor and ceiling colors to two different ones.
*/

int	dot_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 0 && ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (FAILURE);
	return (SUCCESS);
}

t_map	*init_map(char *mapname)
{
	char	*map_path;
	t_map	*my_map;

	if (dot_cub(mapname))
		ft_exit_error("Wrong file extention");
	map_path = ft_strjoin("./maps/", mapname);
	if (!mapname)
		return (FAILURE); 
	my_map = ft_calloc(1, sizeof(t_map));
	if (!my_map)
	{
		free(map_path);
		return (FAILURE);
	}
	if (read_map(map_path, my_map))
	{
		free(map_path);
		free(my_map);
		ft_exit_error("Can't read map");
	}
	free(map_path);
	return (my_map);
}


int init_game(char *mapfile)
{
	t_map	*map;

	map = init_map(mapfile);
	if (!map)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_exit_error("Wrong no of arguments");
		return(FAILURE);
	}
	init_game(av[1]);
	return (SUCCESS);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_so_ea_we.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:29:08 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/18 15:36:15 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	north_path(t_map *map, char *line)
{
	int	fd;

	if (map->north)
		return (FAILURE);
	map->north = ft_strtrim(line + 3, "\n\t\r ");
	fd = open(map->north, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid texture path: %s\n", map->north);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	south_path(t_map *map, char *line)
{
	int	fd;

	if (map->south)
		return (FAILURE);
	map->south = ft_strtrim(line + 3, "\n\t\r ");
	fd = open(map->south, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid texture path: %s\n", map->south);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	east_path(t_map *map, char *line)
{
	int	fd;

	if (map->east)
		return (FAILURE);
	map->east = ft_strtrim(line + 3, "\n\t\r ");
	fd = open(map->east, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid texture path: %s\n", map->east);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	west_path(t_map *map, char *line)
{
	int	fd;

	if (map->west)
		return (FAILURE);
	map->west = ft_strtrim(line + 3, "\n\t\r ");
	fd = open(map->west, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid texture path: %s\n", map->west);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	parse_map_id(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (SUCCESS);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (SUCCESS);
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (SUCCESS);
	else if (ft_strchr(line, WALL))
		return (MAP_START);
	else
		return (FAILURE);
	return (SUCCESS);
}

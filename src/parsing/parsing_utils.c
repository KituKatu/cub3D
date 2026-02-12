/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:52:50 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/12 15:41:08 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		return (FAILURE);
	return (SUCCESS);
}

int	parse_identifier(char *line, t_map *map)
{
	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0))
		floor_ceiling(map, line);
	else if (ft_strncmp(line, "NO ", 3) == 0)
		map->north = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strchr(line, WALL))
		return (FAILURE);
	return (SUCCESS);
}

void	floor_ceiling(t_map *map, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->floor_check > 0)
			return ;
		map->floor_check++;
		line = ft_strtrim(line + 2, "\n\t ");
		map->floor = parse_color(line, map);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->ceiling_check > 0)
			return ;
		map->ceiling_check++;
		line = ft_strtrim(line + 2, "\n\t ");
		map->ceiling = parse_color(line, map);
	}
}

void	map_dimensions(t_map *map)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	height = 1;
	while (map->line[i] && map->line[i] != '\n')
		i++;
	width = i;
	while ((map->line = get_next_line(map->fd)))
	{
		i = 0;
		while (map->line[i] && map->line[i] != '\n')
			i++;
		if (i > width)
			width = i;
		ft_safefree((void *)&map->line);
		height++;
	}
	map->x_len = width;
	map->y_len = height;
	if (map->x_len > 116 || map->y_len > 60)
		ft_exit_errc("Map size error!", (void *)&map, 's');
	close(map->fd);
}

char	**init_grid(t_map *map)
{
	int		i;
	char	**grid;

	i = 0;
	grid = ft_calloc(map->y_len + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	while (i < map->y_len)
	{
		grid[i] = ft_calloc(map->x_len + 1, sizeof(char));
		if (!grid[i])
		{
			ft_freearr((void *)grid);
			return (NULL);
		}
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

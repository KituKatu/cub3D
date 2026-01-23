/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:52:50 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/01/23 14:31:23 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	parse_identifier(char *line, t_map *map)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		line = ft_strtrim(line + 2, "\n\t ");
		map->floor = parse_color(line, map);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		line = ft_strtrim(line + 2, "\n\t ");
		map->ceiling = parse_color(line, map);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
		map->north = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east = ft_strtrim(line + 3, "\n\t ");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west = ft_strtrim(line + 3, "\n\t ");
	else if(ft_strchr(line, WALL))
		return (1);
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	dot_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 0 && ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (FAILURE);
	return (SUCCESS);
}

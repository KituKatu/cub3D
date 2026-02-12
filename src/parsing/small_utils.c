/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:49:59 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/12 13:06:11 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_valid_char(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->y_len)
	{
		j = 0;
		while (j < map->x_len)
		{
			// printf("%s\n", map->grid[i]);
			if (map->grid[i][j] != 'N' && map->grid[i][j] != 'S' && map->grid[i][j] != 'E'
				&& map->grid[i][j] != 'W' && map->grid[i][j] != '1' && map->grid[i][j] != '0'
				&& map->grid[i][j] != ' ')
			{
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	one_player(t_map *map)
{
	int	i;
	int	j;
	int	player_flag;

	i = 0;
	player_flag = 0;
	while (i < map->y_len)
	{
		j = 0;
		while (j < map->x_len)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				player_flag++;
				if (player_flag > 1)
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	if (player_flag <= 0)
		return (FAILURE);
	return (SUCCESS);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
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

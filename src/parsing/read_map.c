/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:50:37 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/12 15:19:08 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_map	*init_map(char *mapname)
{
	char	*map_path;
	t_map	*map;

	if (dot_cub(mapname))
		ft_exit_error("Wrong file extention");
	map_path = ft_strjoin("./maps/", mapname);
	if (!mapname)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		ft_safefree((void *)&map_path);
		return (NULL);
	}
	map->name = map_path;
	if (read_map(map))
	{
		ft_safefree((void *)&map_path);
		ft_exit_errc("Can't read map", (void *)&map, 'm');
	}
	ft_safefree((void *)&map_path);
	return (map);
}

int	read_map(t_map *map)
{
	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	while ((map->line = get_next_line(map->fd)))
	{
		if (empty_line(map->line) == SUCCESS)
		{
			ft_safefree((void *)&map->line);
			continue ;
		}
		if (parse_identifier(map->line, map) == FAILURE)
		{
			map_setup(map);
			break ;
		}
		ft_safefree((void *)&map->line);
	}
	close(map->fd);
	return (SUCCESS);
}

int	read_map_again(t_map *map)
{
	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	while ((map->line = get_next_line(map->fd)))
	{
		if (empty_line(map->line) == SUCCESS)
		{
			ft_safefree((void *)&map->line);
			continue ;
		}
		if (parse_map_id(map->line) == FAILURE)
		{
			parse_map_first_line(map);
			break ;
		}
		ft_safefree((void *)&map->line);
	}
	close(map->fd);
	return (SUCCESS);
}

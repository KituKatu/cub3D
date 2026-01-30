/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:50:37 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/01/27 14:28:07 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	read_map(t_map *map)
{
	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	while((map->line = get_next_line(map->fd)))
	{
		if (empty_line(map->line) == SUCCESS)
		{
			ft_safefree((void*)&map->line);
			continue;
		}
		if (parse_identifier(map->line, map) == FAILURE)
		{
			parse_map_1(map);
			break ;
		}
		ft_safefree((void*)&map->line);
	}
	close(map->fd);
	return (SUCCESS);
}

int	read_map_again(t_map *map)
{
	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	while((map->line = get_next_line(map->fd)))
	{
		if (empty_line(map->line) == SUCCESS)
		{
			ft_safefree((void*)&map->line);
			continue;
		}
		if (parse_identifier(map->line, map) == FAILURE)
		{
			parse_map_2(map);
			break ;
		}
		ft_safefree((void*)&map->line);
	}
	close(map->fd);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:39:35 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/18 15:53:32 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_cubmap(t_map **map)
{
	int	i;

	i = 0;
	ft_safefree((void *)&(*map)->line);
	ft_safefree((void *)&(*map)->north);
	ft_safefree((void *)&(*map)->east);
	ft_safefree((void *)&(*map)->south);
	ft_safefree((void *)&(*map)->west);
	// while((*map)->grid)
	// {
	// 	ft_safefree((void *)&(*map)->grid[i]);
	// 	i++;
	// }
	if ((*map)->grid)
	{
		while((*map)->grid[i])
		{
			ft_safefree((void *)&(*map)->grid[i]);
			i++;
		}
		ft_safefree((void *)&(*map)->grid);
	}
}

void	free_cubgame(t_game **game)
{
	free_cubmap(&(*game)->map);
	ft_safefree((void *)&(*game)->player);
}


void	ft_clean_cubed(void **ptr, char id)
{
	if (id == 'm')
		free_cubmap((t_map **)ptr);
	else if (id == 'g')
		free_cubgame((t_game **)ptr);
	else
		ft_safefree(ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:30:47 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/06 13:32:26 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* spawns player on the map in direction orient
	+0.5 for center of tile
*/ 
void	init_player(t_game *game)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		ft_exit_errc("Failed to init player", (void *)&game, 'g');
	player->posx = game->map->player_x + 0.5;
	player->posy = game->map->player_y + 0.5;
	game->map->grid[game->map->player_y][game->map->player_x] = SPACE;
	init_orient_N_S(game, player);
	game->player = player;
}

void	init_orient_N_S(t_game *game, t_player *player)
{
	if (game->map->orient == 'N')
	{
		player->dirx = 0.0;
		player->diry = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (game->map->orient == 'S')
	{
		player->dirx = 0.0;
		player->diry = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	init_orient_E_W(game, player);
}

void	init_orient_E_W(t_game *game, t_player *player)
{
	if (game->map->orient == 'E')
	{
		player->dirx = 1.0;
		player->diry = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (game->map->orient == 'W')
	{
		player->dirx = -1.0;
		player->diry = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

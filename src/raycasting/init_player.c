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

void	init_player(t_game *game)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		ft_exit_errc("Failed to init player", (void *)&game, 'g');
	player->posX = game->map->player_x + 0.5; // +0.5 for center of tile
	player->posY = game->map->player_y + 0.5;
	init_orient_N_S(game, player);
	game->player = player;
}

void	init_orient_N_S(t_game *game, t_player *player)
{
	if (game->map->orient == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0.0;
	}
	else if (game->map->orient == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0.0;
	}
	init_orient_E_W(game, player);
}

void	init_orient_E_W(t_game *game, t_player *player)
{
	if (game->map->orient == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0.0;
		player->planeY = 0.66;
	}
	else if (game->map->orient == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0.0;
		player->planeY = -0.66;
	}
}

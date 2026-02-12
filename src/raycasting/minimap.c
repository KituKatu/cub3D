/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:31:32 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/12 12:31:55 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"



void render_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while(y < game->map->y_len)
    {
        x = 0; 
        while (x <game->map->x_len)
        {
            mlx_image_to_window(game->mlx, game->img, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
    
}








/*
    render 2d map with player and 
    rays from player to walls (acc to FOV)
*/
void render_minimap(void *game_ptr)
{
    
    t_game *game;
    
    game = (t_game *)game_ptr;

    
    

}
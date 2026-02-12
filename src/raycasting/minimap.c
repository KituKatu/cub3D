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


/*
    render 2D map for the minimap
    rn using textures of 1 wall for all walls
    and general empty img for SPACE
    Ideally this map is only rendered once and not 
    part of the loop
*/
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
            if (game->map->grid[y][x] == WALL)
                mlx_image_to_window(game->mlx, game->map->img[0], x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map->grid[y][x] == SPACE)
                mlx_image_to_window(game->mlx, game->img, x *TILE_SIZE,  y * TILE_SIZE);
            x++;
        }
        y++;
    }

}


/*
    renders representation of 
    the player on the map 
    (prolly good to use a 
    triangle as dir vector)
*/
void render_miniplay(t_game *game)
{

}


/*
    render 2d map with player and 
    rays from player to walls (acc to FOV)
    this function will loop, so needs to 
    contain the raycasting bit 
*/
void render_minimap(void *game_ptr)
{
    
    t_game *game;
    
    game = (t_game *)game_ptr;

    

}
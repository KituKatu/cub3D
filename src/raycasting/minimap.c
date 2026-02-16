/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:31:32 by jmcgrane          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/16 15:54:22 by jmcgrane         ###   ########.fr       */
=======
/*   Updated: 2026/02/16 14:11:59 by jmcgrane         ###   ########.fr       */
>>>>>>> jack
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void render_box(t_game *game, int y, int x, int color)
{
    int offset;
    int i;
    int j;
    
    i = 0;
    j = 0;
    offset = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while(j < TILE_SIZE)
        {
            mlx_put_pixel(game->img, x+j, y +i, color);
            j++;
        }
        i++;
    }
}

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
        while (x < game->map->x_len)
        {
            if (game->map->grid[y][x] == WALL)
                render_box(game, y * TILE_SIZE, x * TILE_SIZE, BLUE);
            else
            // if (game->map->grid[y][x] == SPACE)
                render_box(game, y * TILE_SIZE, x * TILE_SIZE, WHITE);
            x++;
        }
        y++;
    }

}


void render_ray(t_game *game, int color)
{
    int drawStart;
    int size;
    
    drawStart = 0;
    size = 8;
    while(drawStart < size)
    {
        mlx_put_pixel(game->img, (game->player->posX * TILE_SIZE) + (drawStart * game->player->dirX), (game->player->posY * TILE_SIZE) + (drawStart *game->player->dirY), color);
        drawStart++;
    }

}

/*
    renders representation of 
    the player on the map 
    (prolly good to use a triangle)
*/

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
    render_miniplay(game, RED);
    
}
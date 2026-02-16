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


void render_box(t_game *game, int y, int x, int color)
{
    int offset;
    int i;
    int j;
    
    i = 0;
    j = 0;
    offset = 6;
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
        while (x <game->map->x_len)
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
    int x;
    
    drawStart = 0;
    size = 24;
    
    while (drawStart < size/2)
    {
        x = (game->player->posX * TILE_SIZE);
        mlx_put_pixel(game->img, x + (drawStart * game->player->dirX), (game->player->posY * TILE_SIZE) + (drawStart *game->player->dirY), color);
        drawStart++;
    }

}

/*
    renders representation of 
    the player on the map 
    (prolly good to use a triangle)
*/
void render_miniplay(t_game *game, int color)
{   
    int size;
    int x;
    int y; 

    size = 10;
    x = -size  /2;
    while (x < size/2)
    {
        y =  -size /2;
        while (y < size/2)
        {
            if (game->player->posX + x > 0.0 && game->player->posX + x < game->map->x_len * 1.0 && game->player->posY + y > 0.0 && game->player->posY + y < game->map->y_len * 1.0)
                mlx_put_pixel(game->img, game->player->posX * TILE_SIZE + x, game->player->posY * TILE_SIZE +y, color);
            y++;
        }
        x++;
    }
        
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
    render_miniplay(game, RED);

    t_ray ray;
	ray.mapX = game->player->posX;
	ray.mapY = game->player->posY;
	ray.dirX = game->player->dirX;
	ray.dirY = game->player->dirY;

    cast_ray(game, &ray, game->img);
    render_ray(game, YELLOW);
}
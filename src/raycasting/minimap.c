/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:31:32 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/17 12:16:03 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//renders line at position.x from line.x until line.y in color
void render_line(mlx_image_t *img, t_vertex line, t_vertex *position, int color)
{
    int drawStart; 
    int drawEnd;
    // int offset;

    // offset = SCREEN_HEIGHT/4;
    drawStart = line.x;
    drawEnd = line.y;
 	while (drawStart < drawEnd)
	{
		mlx_put_pixel(img, position->x, drawStart, color);
		drawStart++;
	}
}

//renders a box from the 
void render_box(mlx_image_t *img, int y, int x, int color)
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
            mlx_put_pixel(img, x+j, y +i, color);
            j++;
        }
        i++;
    }
}

/*
    render 2D map for the minimap
    rn using textures of 1 wall for all walls
    and general empty img for SPACE
*/
void render_map(t_game *game)
{
    t_vertex pos;
    int offset_x;
    int offset_y;
    int off;

    offset_x = SCREEN_WIDTH/4;
    offset_y = SCREEN_HEIGHT/4;
    pos.y = 0;
    off = 2; 
    game->map_img = mlx_new_image(game->mlx, offset_x, offset_y);
    while (pos.y < game->map->y_len)
    {
        pos.x = 0;
        while (pos.x <game->map->x_len)
        {
            if (game->map->grid[pos.y][pos.x] == WALL)
                render_box(game->img, (pos.y * TILE_SIZE)/off, (pos.x * TILE_SIZE)/off, BLUE);
            else
            // if (game->map->grid[y][x] == SPACE)
                render_box(game->img, (pos.y * TILE_SIZE)/off, (pos.x * TILE_SIZE)/off, WHITE);
            pos.x++;
        }
        pos.y++;
    }

}


bool valid_space(t_game *game, double y, double x)
{
    if (y > 0 && x > 0 && ((game->map->grid[(int)y][(int)x] == SPACE) || (game->map->grid[(int)y][(int)x] == 'N') || (game->map->grid[(int)y][(int)x] == 'E') || (game->map->grid[(int)y][(int)x] == 'S') || (game->map->grid[(int)y][(int)x] == 'W')))
        return (true);
    return (false);
}


/*
    renders single ray from player position
    into dirX and dirY
*/
void render_ray(t_game *game, int size, int color)
{
    int drawStart;
    t_vertex pos;
    
    drawStart = 1;
    while (drawStart < size/2)
    {
        pos.x = (game->player->posX * TILE_SIZE);
        pos.y = (game->player->posY * TILE_SIZE);
        if (valid_space(game, (pos.y + (drawStart *game->player->dirY))/64, (pos.x + (drawStart * game->player->dirX))/64))
            mlx_put_pixel(game->img, (pos.x + (drawStart * game->player->dirX))/2, (pos.y + (drawStart * game->player->dirY))/2, color);
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

    size = 12;
    x = -size  /2;
    while (x < size/2)
    {
        y =  -size /2;
        while (y < size/2)
        {
            if (game->player->posX + x > 0.0 && game->player->posX + x < game->map->x_len * 1.0 && game->player->posY + y > 0.0 && game->player->posY + y < game->map->y_len * 1.0)
                mlx_put_pixel(game->img, (game->player->posX * TILE_SIZE + x)/2, (game->player->posY * TILE_SIZE +y)/2, color);
            y++;
        }
        x++;
    }
        
}


void cast_mapray(t_game *game, t_ray *ray)
{
    int raycount;
    int side;
    double size; 

    raycount = 0;
    while (raycount < 1)
    {
        calc_delta(ray);
        calc_side(game, ray);
        // printf("RAY DISTX = %f\n RAY DISTY = %f\n", ray->sideDistX, ray->sideDistY);
        side = dda(game, ray);
     	if (side == VERTICAL)
		    size = (ray->sideDistX - ray->deltaDistX);
	    else
            size = ray->sideDistY - ray->deltaDistY;
        //render_ray(game, size *2 * TILE_SIZE, WHITE);
        render_ray(game, size *2 * TILE_SIZE, RED);
        printf("RAY SIZE = %f\n", size);
        //render_ray(game, size *2 * TILE_SIZE, WHITE);
        //calc_delta(ray);
        //ray->dirX += DEGREE;
        raycount++;
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
    t_ray ray;

    game = (t_game *)game_ptr;
	ray.mapX = game->player->posX;
	ray.mapY = game->player->posY;
	ray.dirX = game->player->dirX;
	ray.dirY = game->player->dirY;
    
    clear_scene(game->img);
    render_map(game);
    render_miniplay(game, RED);
    cast_mapray(game, &ray);
    cast_ray(game, &ray);
    //render_scene(game);
}
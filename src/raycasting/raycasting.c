/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:38 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/06 13:19:47 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

/*calculate height of walls on grid by raycasting
    calc vector of camera plane?
    direction vector multiplies the pos of player in cert direction (length doesn't matter only dir)
    load in vector lib?
*/

void init_player(t_game *game)
{
    t_player *player;

    player = ft_calloc(1, sizeof(t_player));
    if (!player)
        ft_exit_errc("Failed to init player", (void *)&game, 'g');
    player->posX = game->map->player_x + 0.5; // +0.5 for center of tile
    player->posY = game->map->player_y + 0.5;
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
    else if (game->map->orient == 'E')
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
    game->player = player;
}
//returns the line height of the walls depending on x or y axis is hit by raycast 
//needs a struct for all the arguments 
int calc_height(t_game *game, int side)
{
    double perpWallDist; 


    if (side == 0)
        perpWallDist = (game->player->sideDistX - game->player->deltaDistX);
    else 
        perpWallDist = (game->player->deltaDistX - game->player->deltaDistY);
    return((int)SHEIGHT / perpWallDist); 
}

// calc if ray from camera plane hits wall? --> needs
int val_stray(t_game *game)
{
    int mapX;
    int mapY;
    bool hit;
    int side;
    
    mapX = game->player->dirX;
    mapY = game->player->dirY; 
    while (hit == false)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if (game->player->sideDistX < game->player->deltaDistY)
        {
            game->player->sideDistX += game->player->deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            game->player->sideDistY += game->player->deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (game->map->grid[mapX][mapY] == WALL)
            hit = true;
    }

    
}

//calculate distance ray to wall

void calc_dirX(t_player *play)
{
    //calculate step and initial sideDist
    if (play->dirX < 0)
    {
        stepX = -1;
        play->sideDistX = (play->posX - mapX) * play->deltaDistX;
    }
    else
    {
        stepX = 1;
        play->sideDistX = (mapX + 1.0 - play->posX) * play->deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        play->sideDistY = (play->posY - mapY) * play->deltaDistY;
    }
    else
    {
        stepY = 1;
        play->sideDistY = (mapY + 1.0 - play->posY) * play->deltaDistY;
    }

}

//need function to handle rotation
void rotate_c(t_game **game, char dir)
{
    t_player *play;
    double oldDirX;
    double oldPlaneX;

    play = (*game)->player;
    oldDirX = play->dirX;
    oldPlaneX = play->planeX;
    if (dir == 'l')
    {
        play->dirX = play->dirX * cos(ROTSPEED) - play->dirY * sin(ROTSPEED);
        play->dirY = oldDirX * sin(ROTSPEED) + play->dirY * cos(ROTSPEED);
        play->planeX = play->planeX * cos(ROTSPEED) - play->planeY * sin(ROTSPEED);
        play->planeY = oldPlaneX * sin(ROTSPEED) + play->planeY * cos(ROTSPEED);
    }
    else if (dir == 'r')
    { 
        play->dirX = play->dirX * cos(-ROTSPEED) - play->dirY * sin(-ROTSPEED);
        play->dirY = oldDirX * sin(-ROTSPEED) + play->dirY * cos(-ROTSPEED);
        play->planeX = play->planeX * cos(-ROTSPEED) - play->planeY * sin(-ROTSPEED);
        play->planeY = oldPlaneX * sin(-ROTSPEED) + play->planeY * cos(-ROTSPEED);
    }
}

void move_pl(t_game **game, double y, double x, keys_t dir)
{
    t_player *play;

    play = (*game)->player;
    if (dir == 'f')
    {
        if ((*game)->map->grid[(int)y][(int)(x + play->dirX * MOVSPEED)] == SPACE)
            (*game)->player->posX += play->dirX * MOVSPEED; 
        if ((*game)->map->grid[(int)(y + play->dirY * MOVSPEED)][(int)x] == SPACE)
            (*game)->player->posY += play->dirY * MOVSPEED; 
    }
    else if (dir == 'b')
    {
        if ((*game)->map->grid[(int)y][(int)(x - play->dirX * MOVSPEED)] == SPACE)
            (*game)->player->posX -= play->dirX * MOVSPEED; 
        if ((*game)->map->grid[(int)(y - play->dirY * MOVSPEED)][(int)x] == SPACE)
            (*game)->player->posY -= play->dirY * MOVSPEED; 
    }

}


//need a keyhook where the pos of player is updated 
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
    //needs while loop until EOF 
	t_game	**game;
    
	game = (t_game *)param;
	if (keydown.action == MLX_PRESS || keydown.action == MLX_REPEAT)
	{
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window((*game)->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_pl(game, (*game)->player->posY, (*game)->player->posX, 'f');
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_pl(game, (*game)->player->posY, (*game)->player->posX, 'b');
		if (keydown.key == MLX_KEY_LEFT || keydown.key == MLX_KEY_A)
			rotate_c(game, 'l');
		if (keydown.key == MLX_KEY_RIGHT || keydown.key == MLX_KEY_D)
			rotate_c(game, 'r');
	}
}

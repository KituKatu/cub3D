/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   move_player.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 16:12:27 by adecheri       #+#    #+#                */
/*   Updated: 2026/02/27 16:12:29 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>


/*rotates the camera plane in left or right
	changed macro ROTSPEED to reflect radians
	in stead of degrees -> have to check out 
	if the dirX are still alright -> might need PI conversion too
*/
void	rot_camera(t_game *game, char dir)
{
	t_player	*play;
	double		oldDirX;
	double		oldPlaneX;

	play = game->player;
	oldDirX = play->dirX;
	oldPlaneX = play->planeX;
	if (dir == 'r')
	{
		play->dirX = (play->dirX * cos(ROTSPEED) - play->dirY * sin(ROTSPEED));
		play->dirY = (oldDirX * sin(ROTSPEED) + play->dirY * cos(ROTSPEED));
		play->planeX = play->planeX * cos(ROTSPEED) - play->planeY * sin(ROTSPEED);
		play->planeY = oldPlaneX * sin(ROTSPEED) + play->planeY * cos(ROTSPEED);
	}
	else if (dir == 'l')
	{
		play->dirX = (play->dirX * cos(-ROTSPEED) - play->dirY * sin(-ROTSPEED));
		play->dirY = (oldDirX * sin(-ROTSPEED) + play->dirY * cos(-ROTSPEED));
		play->planeX = play->planeX * cos(-ROTSPEED) - play->planeY
			* sin(-ROTSPEED);
		play->planeY = oldPlaneX * sin(-ROTSPEED) + play->planeY
			* cos(-ROTSPEED);
	}
}

/* updates the player position by checking if the 
	next position is taken by a wall, still needs to check if 
	the sides of the ray from player to wall intersect the collision 
	box of the player when moving through
*/
void	move_fb(t_game *game, double y, double x, keys_t dir)
{
	t_player	*play;

	play = game->player;
	if (dir == 'f')
	{
		if (game->map->grid[(int)floor(y)][(int)floor(x + (play->dirX
				* MOVSPEED))] != WALL)
			game->player->posX += play->dirX * MOVSPEED;
		if (game->map->grid[(int)floor(y + (play->dirY
				* MOVSPEED))][(int)floor(x)] != WALL)
			game->player->posY += play->dirY * MOVSPEED;
	}
	else if (dir == 'b')
	{
		if (game->map->grid[(int)floor(y)][(int)floor(x - play->dirX
				* MOVSPEED)] != WALL)
			game->player->posX -= play->dirX * MOVSPEED;
		if (game->map->grid[(int)floor(y - play->dirY
				* MOVSPEED)][(int)floor(x)] != WALL)
			game->player->posY -= play->dirY * MOVSPEED;
	}
}


/*
	needs to have the absolute coordinates 
	of intersection of wall to check 4 sides?
	--> no jumping between grid points 
*/
bool val_step(t_game *game, t_vertex pos, double delta)
{

	if (game->map->grid[(int)floor(pos.y)][(int)floor(pos.x + delta)] != WALL)
		return(false);
	
	return (true);
}





/* updates the player position by checking if the 
	next position is taken by a wall, still needs to check if 
	the sides of the ray from player to wall intersect the collision 
	box of the player when moving through 
	TODO: make func validating intersections of pl box with walls
*/
void	move_lr(t_game *game, double y, double x, keys_t dir)
{
	t_player	*play;
	double		delta;

	play = game->player;
	delta = 0;

	if (dir == 'l')
	{
		delta = (play->planeX * play->dirX * MOVSPEED);
		if (game->map->grid[(int)floor(y)][(int)floor(x + delta)] != WALL)
			game->player->posX -= delta;
		if (game->map->grid[(int)floor(y - play->planeY * (play->dirY
				* MOVSPEED))][(int)floor(x)] != WALL)
			game->player->posY += play->planeY * play->dirY * MOVSPEED;
	}
	else if (dir == 'r')
	{
		if (game->map->grid[(int)floor(y)][(int)floor(x - play->planeX * play->dirX
				* MOVSPEED)] != WALL)
			game->player->posX += play->planeX * play->dirX * MOVSPEED;
		if (game->map->grid[(int)floor(y +  play->planeY * play->dirY
				* MOVSPEED)][(int)floor(x)] != WALL)
			game->player->posY -= play->planeY * play->dirY * MOVSPEED;
	}
}

void toggle_minimap(t_game *game)
{
	if (game->map_img->enabled)
		game->map_img->enabled = false;
	else 
		game->map_img->enabled = true;
}

// keyhook to process player input 
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydown.action == MLX_PRESS || keydown.action == MLX_REPEAT)
	{
		render_miniplay(game, WHITE);
		render_ray(game, 24, WHITE);
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_fb(game, game->player->posY, game->player->posX, 'f');
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_fb(game, game->player->posY, game->player->posX, 'b');
		if (keydown.key == MLX_KEY_A)
			move_lr(game, game->player->posY, game->player->posX, 'l');
		if (keydown.key == MLX_KEY_D)
			move_lr(game, game->player->posY, game->player->posX, 'r');
		if (keydown.key == MLX_KEY_LEFT)
			rot_camera(game, 'l');
		if (keydown.key == MLX_KEY_RIGHT)
			rot_camera(game, 'r');
		if (keydown.key == MLX_KEY_M)
		 	toggle_minimap(game);
	}
	render_miniplay(game, RED);
	render_ray(game, 24, RED);
	printf("PLAYER X: %f\n PLAYER Y: %f\n", game->player->posX, game->player->posY);
	// printf("PLAYER DIRX: %f\n PLAYER DIRY: %f\n", game->player->dirX, game->player->dirY);
	// printf("PLAYER PLANEX: %f\n PLAYER PLANEY: %f\n", game->player->planeX, game->player->planeY);
}

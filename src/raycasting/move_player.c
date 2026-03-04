/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:12:27 by adecheri          #+#    #+#             */
/*   Updated: 2026/03/04 12:41:15 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

static bool	is_wall(t_game *game, double y, double x)
{
	int	iy;
	int	ix;

	iy = (int)floor(y);
	ix = (int)floor(x);
	if (iy < 0 || iy >= game->map->y_len || ix < 0
		|| ix >= game->map->x_len)
		return (true);
	return (game->map->grid[iy][ix] == WALL);
}

/*rotates the camera plane in left or right
	by ROTSPEED macro
*/
void	rot_camera(t_game *game, char dir, double speed)
{
	t_player	*play;
	double		oldDirX;
	double		oldPlaneX;

	speed *= game->mlx->delta_time;
	if (speed > 0.2)
		speed = 0.2;
	play = game->player;
	oldDirX = play->dirx;
	oldPlaneX = play->plane_x;
	if (dir == 'r')
	{
		play->dirx = (play->dirx * cos(speed) - play->diry * sin(speed));
		play->diry = (oldDirX * sin(speed) + play->diry * cos(speed));
		play->plane_x = play->plane_x * cos(speed) - play->plane_y * sin(speed);
		play->plane_y = oldPlaneX * sin(speed) + play->plane_y * cos(speed);
	}
	else if (dir == 'l')
	{
		play->dirx = (play->dirx * cos(-speed) - play->diry * sin(-speed));
		play->diry = (oldDirX * sin(-speed) + play->diry * cos(-speed));
		play->plane_x = play->plane_x * cos(-speed) - play->plane_y
			* sin(-speed);
		play->plane_y = oldPlaneX * sin(-speed) + play->plane_y
			* cos(-speed);
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
	double		speed;

	speed = MOVSPEED * game->mlx->delta_time;
	if (speed > 0.4)
		speed = 0.4;
	play = game->player;
	if (dir == 'f')
	{
		if (!is_wall(game, y, x + play->dirx * speed))
			game->player->posx += play->dirx * speed;
		if (!is_wall(game, y + play->diry * speed, x))
			game->player->posy += play->diry * speed;
	}
	else if (dir == 'b')
	{
		if (!is_wall(game, y, x - play->dirx * speed))
			game->player->posx -= play->dirx * speed;
		if (!is_wall(game, y - play->diry * speed, x))
			game->player->posy -= play->diry * speed;
	}
}


/*
	needs to have the absolute coordinates 
	of intersection of wall to check 4 sides?
	--> no jumping between grid points 
*/
bool val_step(t_game *game, t_vertex pos, double delta)
{
	if (!is_wall(game, pos.y, pos.x + delta))
		return(false);	
	return (true);
}



/* updates the player position by checking if the 
	next position is taken by a wall, still needs to check if 
	the sides of the ray from player to wall intersect the collision 
	box of the player when moving through 
*/
void	move_lr(t_game *game, double y, double x, keys_t dir)
{
	t_player	*play;
	double		dx;
	double 		dy;
	double		speed;

	speed = MOVSPEED * game->mlx->delta_time;
	if (speed > 0.4)
		speed = 0.4;
	play = game->player;
	dx = ( play->dirx * speed);
	dy = ( play->diry * speed);
	if (dir == 'r')
	{
		if (!is_wall(game, y, x - dy))
			game->player->posx -= dy;
		if (!is_wall(game, y + dx, x))
			game->player->posy += dx;
	}
	else if (dir == 'l')
	{
		if (!is_wall(game, y, x + dy))
			game->player->posx += dy;
		if (!is_wall(game, y - dx, x))
			game->player->posy -= dx;
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
		game->player->moving = true;
		render_miniplay(game, WHITE);
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_fb(game, game->player->posy, game->player->posx, 'f');
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_fb(game, game->player->posy, game->player->posx, 'b');
		if (keydown.key == MLX_KEY_A)
			move_lr(game, game->player->posy, game->player->posx, 'l');
		if (keydown.key == MLX_KEY_D)
			move_lr(game, game->player->posy, game->player->posx, 'r');
		if (keydown.key == MLX_KEY_LEFT)
			rot_camera(game, 'l', ROTSPEED);
		if (keydown.key == MLX_KEY_RIGHT)
			rot_camera(game, 'r', ROTSPEED);
		if (keydown.key == MLX_KEY_M)
		 	toggle_minimap(game);
	}
	render_miniplay(game, RED);
}

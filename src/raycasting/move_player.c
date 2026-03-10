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
	if (iy < 0 || iy >= game->map->y_len || ix < 0 || ix >= game->map->x_len)
		return (true);
	return (game->map->grid[iy][ix] == WALL);
}

/*rotates the camera plane in left or right
	by ROTSPEED macro. If the speed is neg,
	the rotation is left (ccw), when speed is pos,
	the rotation is to the righ (cw)
*/
void	rot_camera(t_game *game, double speed)
{
	t_player	*play;
	double		olddirx;
	double		oldplanex;

	speed *= game->mlx->delta_time;
	if (speed > 0.2)
		speed = 0.2;
	play = game->player;
	olddirx = play->dirx;
	oldplanex = play->plane_x;
	play->dirx = (play->dirx * cos(speed) - play->diry * sin(speed));
	play->diry = (olddirx * sin(speed) + play->diry * cos(speed));
	play->plane_x = play->plane_x * cos(speed) - play->plane_y * sin(speed);
	play->plane_y = oldplanex * sin(speed) + play->plane_y * cos(speed);
}

/* updates the player position by checking if the 
	next position is taken by a wall, still needs to check if 
	the sides of the ray from player to wall intersect the collision 
	box of the player when moving through
*/
void	move_fb(t_game *game, t_vertex pos, keys_t dir, double speed)
{
	t_player	*play;
	double		dir_s;

	if (speed > 0.4)
		speed = 0.4;
	play = game->player;
	if (dir == MLX_KEY_UP || dir == MLX_KEY_W)
	{
		dir_s = play->dirx * speed;
		if (!is_wall(game, pos.y, pos.x + dir_s))
			game->player->posx += dir_s;
		dir_s = play->diry * speed;
		if (!is_wall(game, pos.y + dir_s, pos.x))
			game->player->posy += dir_s;
	}
	else if (dir == MLX_KEY_S || dir == MLX_KEY_DOWN)
	{
		dir_s = play->dirx * speed;
		if (!is_wall(game, pos.y, pos.x - dir_s))
			game->player->posx -= dir_s;
		dir_s = play->diry * speed;
		if (!is_wall(game, pos.y - dir_s, pos.x))
			game->player->posy -= dir_s;
	}
}

/* updates the player position by checking if the 
	next position is taken by a wall, still needs to check if 
	the sides of the ray from player to wall intersect the collision 
	box of the player when moving through 
*/
void	move_lr(t_game *game, t_vertex pos, keys_t dir, double speed)
{
	t_player	*play;
	double		dx;
	double		dy;

	if (speed > 0.4)
		speed = 0.4;
	play = game->player;
	dx = (play->dirx * speed);
	dy = (play->diry * speed);
	if (dir == MLX_KEY_D)
	{
		if (!is_wall(game, pos.y, pos.x - dy))
			game->player->posx -= dy;
		if (!is_wall(game, pos.y + dx, pos.x))
			game->player->posy += dx;
	}
	else if (dir == MLX_KEY_A)
	{
		if (!is_wall(game, pos.y, pos.x + dy))
			game->player->posx += dy;
		if (!is_wall(game, pos.y - dx, pos.x))
			game->player->posy -= dx;
	}
}

// keyhook to process player input
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
	t_game		*game;
	t_vertex	pos;
	double		speed;

	game = (t_game *)param;
	pos.x = game->player->posx;
	pos.y = game->player->posy;
	speed = MOVSPEED * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, keydown.key) == true)
	{
		render_miniplay(game, WHITE);
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		move_fb(game, pos, keydown.key, speed);
		move_lr(game, pos, keydown.key, speed);
		if (keydown.key == MLX_KEY_LEFT)
			rot_camera(game, -ROTSPEED);
		if (keydown.key == MLX_KEY_RIGHT)
			rot_camera(game, ROTSPEED);
		if (keydown.key == MLX_KEY_M)
			game->map_img->enabled = !game->map_img->enabled;
	}
	render_miniplay(game, RED);
	game->player->moving = false;
}

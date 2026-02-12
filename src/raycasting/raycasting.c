/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:38 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/06 13:31:40 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

/*calculate height of walls on grid by raycasting
	calc vector of camera plane?
	direction vector multiplies the pos of player in cert direction (length doesn't matter only dir)
*/

int init_ray(t_game *game)
{
	t_ray *ray;
	double cameraX;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (FAILURE);
	ray->mapX = game->player->posX;
	ray->mapY = game->player->posY;	
}

void cast_ray(t_game *game, t_ray *ray)
{
	int x;
	double cameraX;

	x = 0; 
	while (x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH -1;
		ray->dirX = game->player->dirX * game->player->planeX *cameraX;
		ray->dirY = game->player->dirY * game->player->planeY *cameraX;
		ray->mapX = game->player->posX;
		ray->mapY = game->player->posY;
		calc_side(game, ray);
		dda(game, ray);
		calc_delta(game, ray);
		x++;
	}
}



void calc_delta(t_game *game, t_ray *ray)
{
	if (ray->dirX == 0)
		ray->dirX = 1e30; 
	else
		ray->deltaDistX = fabs(1 / ray->dirX);  
	if (ray->dirY == 0)
		ray->dirY = 1e30;
	else 
		ray->deltaDistY = fabs(1 / ray->dirY);
}


// returns the line height of the walls depending on x or y axis is hit by raycast
// needs a struct for all the arguments
void	calc_height(t_game *game, t_ray *ray, int side)
{
	double	perpWallDist;
	int drawStart;
	int drawEnd;
	int x; // defines spot where ray is drawn in image

	x = SCREEN_WIDTH/2;
	//color = 16777215; //white decimal (0xFFFFFFFF)
	if (side == VERTICAL)
		perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		perpWallDist = (ray->deltaDistX - ray->deltaDistY);
	ray->lineHeight = (int)SCREEN_HEIGHT / perpWallDist;

	drawStart = -ray->lineHeight/2 + SCREEN_HEIGHT /2;
	if (drawStart < 0)
		drawStart = 0; 
	drawEnd = ray->lineHeight/2 + SCREEN_HEIGHT /2;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;
	while (drawStart < drawEnd)
	{
		mlx_put_pixel(game->mlx, x, drawStart, 0xFFFFFFFF);
		drawStart++;
	}
}

// calc if ray from camera plane hits wall
// with side defining if the wall is NS or EW
void	dda(t_game *game, t_ray *ray)
{
	int		mapX;
	int		mapY;
	bool	hit;
	int		side;

	mapX = game->player->posX;
	mapY = game->player->posY;
	while (hit == false)
	{
		if (ray->sideDistX < ray->deltaDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			mapX += ray->stepX;
			side = VERTICAL;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			mapY += ray->stepY;
			side = HORIZONTAL;
		}
		if (game->map->grid[mapX][mapY] == WALL)
			hit = true;
	}
	calc_height(game, ray, side);
}

/* calculate distance ray to wall
	
*/
void	calc_side(t_game *game, t_ray *ray)
{
	
	// calculate step and initial sideDist
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player->posX - game->map->player_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->player->posX) * ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player->posY) * ray->deltaDistY;
	}
}

/*rotates the camera plane in left or right
	direction according to player input 
*/
void	rot_camera(t_game **game, char dir)
{
	t_player	*play;
	double		oldDirX;
	double		oldPlaneX;

	play = (*game)->player;
	oldDirX = play->dirX;
	oldPlaneX = play->planeX;
	if (dir == 'l')
	{
		play->dirX = play->dirX * cos(ROTSPEED) - play->dirY * sin(ROTSPEED) *FOV;
		play->dirY = oldDirX * sin(ROTSPEED) + play->dirY * cos(ROTSPEED) * FOV;
		play->planeX = play->planeX * cos(ROTSPEED) - play->planeY
			* sin(ROTSPEED);
		play->planeY = oldPlaneX * sin(ROTSPEED) + play->planeY * cos(ROTSPEED);
	}
	else if (dir == 'r')
	{
		play->dirX = play->dirX * cos(-ROTSPEED) - play->dirY * sin(-ROTSPEED) * FOV;
		play->dirY = oldDirX * sin(-ROTSPEED) + play->dirY * cos(-ROTSPEED) * FOV;
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
void	move_pl(t_game **game, double y, double x, keys_t dir)
{
	t_player	*play;

	play = (*game)->player;
	if (dir == 'f')
	{
		if ((*game)->map->grid[(int)y][(int)(x + play->dirX
				* MOVSPEED)] == SPACE)
			(*game)->player->posX += play->dirX * MOVSPEED;
		if ((*game)->map->grid[(int)(y + play->dirY
				* MOVSPEED)][(int)x] == SPACE)
			(*game)->player->posY += play->dirY * MOVSPEED;
	}
	else if (dir == 'b')
	{
		if ((*game)->map->grid[(int)y][(int)(x - play->dirX
				* MOVSPEED)] == SPACE)
			(*game)->player->posX -= play->dirX * MOVSPEED;
		if ((*game)->map->grid[(int)(y - play->dirY
				* MOVSPEED)][(int)x] == SPACE)
			(*game)->player->posY -= play->dirY * MOVSPEED;
	}
	
}


// keyhook to process player input 
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
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

/*redraws black all over the scene to clear mlx img
	for the next frame (no ghosting)
*/ 
void clear_scene(t_game *game)
{
	int x;
	int y;
	
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while(x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->mlx, x, y, 0);
			x++;
		}
		y++;
	}
}



void render_scene(t_game *game, t_ray *ray)
{
	// double oldtime;
	// double frame_time;

	// oldtime = mlx_get_time();

	// dda(game, ray);
	// calc_side(game, ray);
	// calc_delta(game, ray);
	cast_ray(game, ray);
	clear_scene(game);

}
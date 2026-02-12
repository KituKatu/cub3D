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

void calc_delta(t_ray *ray)
{
	if (ray->dirX == 0)
		ray->dirX = 1e30; 
	else
		ray->deltaDistX = fabs(1.0 / ray->dirX);  
	if (ray->dirY == 0)
		ray->dirY = 1e30;
	else 
		ray->deltaDistY = fabs(1.0 / ray->dirY);
}



// returns the line height of the walls depending on x or y axis is hit by raycast
// needs a struct for all the arguments
void	calc_height(t_ray *ray, int side, int x, mlx_image_t *img)
{
	double	perpWallDist;
	int drawStart;
	int drawEnd;
	//color = 16777215; //white decimal (0xFFFFFFFF)
	drawStart= 0;
	drawEnd = 0; 

	if (side == VERTICAL)
		perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		perpWallDist = (ray->deltaDistY - ray->deltaDistY);
	ray->lineHeight = (int)SCREEN_HEIGHT / perpWallDist;

	drawStart = -ray->lineHeight/2 + SCREEN_HEIGHT /2;
	if (drawStart < 0)
		drawStart = 0; 
	drawEnd = ray->lineHeight/2 + SCREEN_HEIGHT /2;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;

	while (drawStart < drawEnd)
	{
		mlx_put_pixel(img, x, drawStart, 0xFFFFFFFF);
		drawStart++;
	}
}

// calc if ray from camera plane hits wall
// with side defining if the wall is NS or EW
bool	dda(t_game *game, t_ray *ray)
{
	bool	hit;
	bool	side;

	hit = false; 
	while (hit == false)
	{
		if (ray->sideDistX < ray->deltaDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			side = VERTICAL;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			side = HORIZONTAL;
		}
		if (game->map->grid[ray->mapY][ray->mapX] == WALL)
			hit = true; 
	}
	return (side);
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
void	rot_camera(t_game *game, char dir)
{
	t_player	*play;
	double		oldDirX;
	double		oldPlaneX;

	play = game->player;
	oldDirX = play->dirX;
	oldPlaneX = play->planeX;
	if (dir == 'l')
	{
		play->dirX = play->dirX * cos(ROTSPEED) - play->dirY * sin(ROTSPEED);
		play->dirY = oldDirX * sin(ROTSPEED) + play->dirY * cos(ROTSPEED);
		play->planeX = play->planeX * cos(ROTSPEED) - play->planeY
			* sin(ROTSPEED);
		play->planeY = oldPlaneX * sin(ROTSPEED) + play->planeY * cos(ROTSPEED);
	}
	else if (dir == 'r')
	{
		play->dirX = play->dirX * cos(-ROTSPEED) - play->dirY * sin(-ROTSPEED);
		play->dirY = oldDirX * sin(-ROTSPEED) + play->dirY * cos(-ROTSPEED);
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
void	move_pl(t_game *game, double y, double x, keys_t dir)
{
	t_player	*play;

	play = game->player;
	if (dir == 'f')
	{
		if (game->map->grid[(int)y][(int)(x + play->dirX
				* MOVSPEED)] == SPACE)
			game->player->posX += play->dirX * MOVSPEED;
		if (game->map->grid[(int)(y + play->dirY
				* MOVSPEED)][(int)x] == SPACE)
			game->player->posY += play->dirY * MOVSPEED;
	}
	else if (dir == 'b')
	{
		if (game->map->grid[(int)y][(int)(x - play->dirX
				* MOVSPEED)] == SPACE)
			game->player->posX -= play->dirX * MOVSPEED;
		if (game->map->grid[(int)(y - play->dirY
				* MOVSPEED)][(int)x] == SPACE)
			game->player->posY -= play->dirY * MOVSPEED;
	}
	
}


// keyhook to process player input 
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydown.action == MLX_PRESS || keydown.action == MLX_REPEAT)
	{
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_pl(game, game->player->posY, game->player->posX, 'f');
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_pl(game, game->player->posY, game->player->posX, 'b');
		if (keydown.key == MLX_KEY_LEFT || keydown.key == MLX_KEY_A)
			rot_camera(game, 'l');
		if (keydown.key == MLX_KEY_RIGHT || keydown.key == MLX_KEY_D)
			rot_camera(game, 'r');
	}
	printf("PLAYER X: %d\n PLAYER Y: %d\n", game->player->posX, game->player->posY);
	printf("PLAYER DIRX: %f\n PLAYER DIRY: %f\n", game->player->dirX, game->player->dirY);
}

/*redraws black all over the scene to clear mlx img
	for the next frame (no ghosting)
	{
*/ 
void clear_scene(mlx_image_t *img)
{
	int x;
	int y;
	
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while(x < SCREEN_WIDTH)
		{
			mlx_put_pixel(img, x, y, 0);
			x++;
		}
		y++;
	}
}


void cast_ray(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int x;
	int side; 
	double cameraX;

	x = 0;
	side = -1;
	while (x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH -1;
		ray->dirX = game->player->dirX * game->player->planeX *cameraX;
		ray->dirY = game->player->dirY * game->player->planeY *cameraX;
		ray->mapX = game->player->posX;
		ray->mapY = game->player->posY;
		calc_side(game, ray);
		side = dda(game, ray);
		calc_height(ray, side, x, img);
		calc_delta(ray);
		x++;
	}
}

void render_scene(void *ptr)
{
	t_game *game; 

	game = (t_game *)ptr; 
	t_ray ray;
	ray.mapX = game->player->posX;
	ray.mapY = game->player->posY;
	ray.dirX = game->player->dirX;
	ray.dirY = game->player->dirY;
	// double oldtime;
	// double frame_time;

	// oldtime = mlx_get_time();

	clear_scene(game->img);
	cast_ray(game, &ray, game->img);
}	

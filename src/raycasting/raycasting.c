/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:38 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/20 14:33:11 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

//TODO: make func to check intersecting rays with play->mov -->walls
//TODO: rendering rays from play->pos until wall=hit 



// calc if ray from camera plane hits wall
// with side defining if the wall is NS or EW
bool	dda(t_game *game, t_ray *ray)
{
	bool	hit;
	bool	side;

	hit = false; 
	while (hit == false)
	{
		calc_side(game, ray);
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
		if (game->map->grid[(int)ray->mapY][(int)ray->mapX] == WALL)
			hit = true; 
	}
	return (side);
}



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
void	move_pl(t_game *game, double y, double x, keys_t dir)
{
	t_player	*play;

	play = game->player;
	if (dir == 'f')
	{
		if (game->map->grid[(int)y][(int)(x + (play->dirX
				* MOVSPEED))] == SPACE)
			game->player->posX += play->dirX * MOVSPEED;
		if (game->map->grid[(int)(y + (play->dirY
				* MOVSPEED))][(int)x] == SPACE)
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


/*redraws black all over the scene to clear mlx img
	for the next frame (no ghosting)
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


void cast_ray(t_game *game, t_ray *ray)
{
	int side; 
	double cameraX;
	t_vertex line_h;
	t_vertex position;
	
	position.x = 1;
	side = -1;
	while (position.x < SCREEN_WIDTH)
	{
		cameraX = 2 * position.x / (double)SCREEN_WIDTH -1;
		ray->dirX = game->player->dirX + game->player->planeX *cameraX;
		ray->dirY = game->player->dirY + game->player->planeY *cameraX;
		ray->mapX = game->player->posX;
		ray->mapY = game->player->posY;

		calc_delta(ray);
		side = dda(game, ray);
		ray->side = side;
		calc_wallDist(ray, side);
		line_h = calc_height(ray);
		// line_h.x += (SCREEN_HEIGHT/2);
		// render_line(game->img, line_h, &position, WHITE);
		render_textured_line(game, ray, line_h, &position);
		position.x++;
	}
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
			move_pl(game, game->player->posY, game->player->posX, 'f');
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_pl(game, game->player->posY, game->player->posX, 'b');
		if (keydown.key == MLX_KEY_LEFT || keydown.key == MLX_KEY_A)
			rot_camera(game, 'l');
		if (keydown.key == MLX_KEY_RIGHT || keydown.key == MLX_KEY_D)
			rot_camera(game, 'r');
		// if (keydown.key == MLX_KEY_M)
		//  	toggle_minimap(game);
	}
	render_miniplay(game, RED);
	render_ray(game, 24, RED);
	printf("PLAYER X: %f\n PLAYER Y: %f\n", game->player->posX, game->player->posY);
	printf("PLAYER DIRX: %f\n PLAYER DIRY: %f\n", game->player->dirX, game->player->dirY);
	// printf("PLAYER PLANEX: %f\n PLAYER PLANEY: %f\n", game->player->planeX, game->player->planeY);
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
	cast_ray(game, &ray);
}	

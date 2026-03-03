/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:38:38 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/25 12:29:15 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

//TODO: make func to check intersecting rays with play->mov -->walls


//&& (ray->mapX > 0 || ray->mapY > 0 || ray->mapX < game->map->x_len || ray->mapY < game->map->y_len)
// calc if ray from camera plane hits wall
// with side defining if the wall is NS or EW
bool	dda(t_game *game, t_ray *ray)
{
	bool	hit;
	int		side;

	hit = false;
	side = 0;
	while (hit == false)
	{
		if (ray->sideDistX < ray->sideDistY)
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
		if ((int)ray->mapX < 0 || (int)ray->mapX >= game->map->x_len
			|| (int)ray->mapY < 0 || (int)ray->mapY >= game->map->y_len)
			break ;
		if (game->map->grid[(int)(ray->mapY)][(int)(ray->mapX)] == WALL)
			hit = true;
	}
	return (side);
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
	
	position.x = 0;
	side = -1;
	while (position.x < SCREEN_WIDTH)
	{
		cameraX = 2 * position.x / (double)SCREEN_WIDTH - 1;
		ray->dirX = game->player->dirX + game->player->planeX * cameraX;
		ray->dirY = game->player->dirY + game->player->planeY * cameraX;
		ray->mapX = (int)game->player->posX;
		ray->mapY = (int)game->player->posY;
		calc_delta(ray);
		calc_side(game, ray);
		side = dda(game, ray);
		ray->side = side;
		calc_wallDist(game, ray, side);
	//	printf("PERPWALL = %f\n", ray->perpWallDist);
		line_h = calc_height(ray);
		render_textured_line(game, ray, line_h, &position);
		position.x++;
	}
}




void render_scene(void *ptr)
{
	t_game *game; 
	t_ray ray;
	double delta_time;
	t_vertex old_mouse;
	
	game = (t_game *)ptr;
	old_mouse = check_mouse(game);
	delta_time = mlx_get_time();
	// ray.mapX = game->player->posX;
	// ray.mapY = game->player->posY;
	ray.dirX = game->player->dirX;
	ray.dirY = game->player->dirY;
	clear_scene(game->img);
	cast_ray(game, &ray);
	if (game->map_img->enabled)
		render_minimap(game);

	mouse_rot(game, old_mouse);
}	

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
	side = -1;
	while (hit == false)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->d_distx;
			ray->mapx += ray->stepx;
			side = VERTICAL;
		}
		else
		{
			ray->side_dy += ray->d_disty;
			ray->mapy += ray->stepy;
			side = HORIZONTAL;
		}
		if ((int)ray->mapx < 0 || (int)ray->mapx >= game->map->x_len
			|| (int)ray->mapy < 0 || (int)ray->mapy >= game->map->y_len)
			break ;
		if (game->map->grid[(int)(ray->mapy)][(int)(ray->mapx)] == WALL)
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
	double cam_x;
	t_vertex line_h;
	t_vertex position;
	
	position.x = 0;
	side = -1;
	while (position.x < SCREEN_WIDTH)
	{
		cam_x = 2 * position.x / (double)SCREEN_WIDTH - 1;
		ray->dirx = game->player->dirx + game->player->plane_x * cam_x;
		ray->diry = game->player->diry + game->player->plane_y * cam_x;
		ray->mapx = (int)game->player->posx;
		ray->mapy = (int)game->player->posy;
		calc_delta(ray);
		calc_side(game, ray);
		side = dda(game, ray);
		ray->side = side;
		calc_walldist(game, ray, side);
		line_h = calc_height(ray);
		render_textured_line(game, ray, line_h, &position);
		position.x++;
	}
}




void render_scene(void *ptr)
{
	t_game *game; 
	t_ray ray;
	t_vertex old_mouse;
	
	game = (t_game *)ptr;
	old_mouse = check_mouse(game);
	ray.dirx = game->player->dirx;
	ray.diry = game->player->diry;
	clear_scene(game->img);
	cast_ray(game, &ray);
	if (game->map_img->enabled)
		render_minimap(game);
	mouse_rot(game, old_mouse);
	// if (game->player->moving)
		
}	

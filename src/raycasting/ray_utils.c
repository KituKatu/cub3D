/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:29:32 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/25 12:29:04 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*calculate height of walls on grid by raycasting
	calc vector of camera plane?
	direction vector multiplies the pos of player in cert direction (length doesn't matter only dir)
*/
void calc_delta(t_ray *ray)
{
	if (ray->dirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1.0 / ray->dirX);
	if (ray->dirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1.0 / ray->dirY);
}


void calc_wallDist(t_game *game, t_ray *ray, int side)
{
	if (side == VERTICAL)
		ray->perpWallDist = (ray->mapX - game->player->posX
			+ (1 - ray->stepX) / 2) / ray->dirX;
	else
		ray->perpWallDist = (ray->mapY - game->player->posY
			+ (1 - ray->stepY) / 2) / ray->dirY;
	if (ray->perpWallDist < 0.0001)
		ray->perpWallDist = 0.0001;
}




// returns the line height of the walls depending on x or y axis is hit by raycast
// needs a struct for all the arguments
t_vertex	calc_height(t_ray *ray)
{
	t_vertex line;
	double line_h;

	line.x = 0;
	line.y = 0; 
	line_h = (int)SCREEN_HEIGHT / ray->perpWallDist;
	ray->line_height = (int)line_h;
	//printf("LINE H = %f\n", line_h);
	line.x = -line_h/2 + (SCREEN_HEIGHT /2);
	if (line.x < 0)
		line.x = 0; 
	line.y = line_h/2 + (SCREEN_HEIGHT /2);
	if (line.y >= SCREEN_HEIGHT)
		line.y = SCREEN_HEIGHT - 1;
	// printf("LINE X = %d\n", line.x);
	// printf("LINE Y = %d\n", line.y);
	return (line);
}

/* calculate where ray intersects 
	with either y or x axis on the mapgrid	
*/
void	calc_side(t_game *game, t_ray *ray)
{
	// calculate step and initial sideDist
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player->posX - ray->mapX) * ray->deltaDistX;
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


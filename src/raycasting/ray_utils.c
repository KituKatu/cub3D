/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:29:32 by adecheri          #+#    #+#             */
/*   Updated: 2026/03/03 12:48:08 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*calculate height of walls on grid by raycasting
	calc vector of camera plane?
	direction vector multiplies the pos of player in cert direction (length doesn't matter only dir)
*/
void calc_delta(t_ray *ray)
{
	if (ray->dirx == 0)
		ray->d_distx = 1e30;
	else
		ray->d_distx = fabs(1.0 / ray->dirx);
	if (ray->diry == 0)
		ray->d_disty = 1e30;
	else
		ray->d_disty = fabs(1.0 / ray->diry);
}


void calc_walldist(t_game *game, t_ray *ray, int side)
{
	if (side == VERTICAL)
		ray->perp_walldist = (ray->mapx - game->player->posx
			+ (1 - ray->stepx) / 2) / ray->dirx;
	else
		ray->perp_walldist = (ray->mapy - game->player->posy
			+ (1 - ray->stepy) / 2) / ray->diry;
	if (ray->perp_walldist < 0.0001)
		ray->perp_walldist = 0.0001;
}


// returns the line height of the walls depending on x or y axis is hit by raycast
// needs a struct for all the arguments
t_vertex	calc_height(t_ray *ray)
{
	t_vertex line;
	double line_h;

	line.x = 0;
	line.y = 0; 
	line_h = (int)SCREEN_HEIGHT / ray->perp_walldist;
	ray->line_height = (int)line_h;
	line.x = -line_h/2 + (SCREEN_HEIGHT /2);
	if (line.x < 0)
		line.x = 0; 
	line.y = line_h/2 + (SCREEN_HEIGHT /2);
	if (line.y >= SCREEN_HEIGHT)
		line.y = SCREEN_HEIGHT - 1;
	return (line);
}


/* calculate where ray intersects 
	with either y or x axis on the mapgrid	
*/
void	calc_side(t_game *game, t_ray *ray)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_dx = (game->player->posx - ray->mapx) * ray->d_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_dx = (ray->mapx + 1.0 - game->player->posx) * ray->d_distx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_dy = (game->player->posy - ray->mapy) * ray->d_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_dy = (ray->mapy + 1.0 - game->player->posy) * ray->d_disty;
	}
}


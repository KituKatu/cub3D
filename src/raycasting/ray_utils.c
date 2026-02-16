/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ray_utils.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/11 12:29:32 by adecheri       #+#    #+#                */
/*   Updated: 2026/02/11 12:29:33 by adecheri       ########   odam.nl        */
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
	int		drawStart;
	int		drawEnd;

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
		mlx_put_pixel(img, x, drawStart, WHITE);
		drawStart++;
	}
}

/* calculate distance ray to wall
	
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

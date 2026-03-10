/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:31:32 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/03/03 12:26:54 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//&& game->player->dirY < 0
bool	valid_space(t_game *game, double y, double x)
{
	if (y > 0 && x > 0 && (int)y < game->map->y_len && (int)x < game->map->x_len
		&& ((game->map->grid[(int)(y)][(int)x] == SPACE)
			|| (game->map->grid[(int)y][(int)x] == 'N')
			|| (game->map->grid[(int)y][(int)x] == 'E')
			|| (game->map->grid[(int)y][(int)x] == 'S')
			|| (game->map->grid[(int)y][(int)x] == 'W')))
		return (true);
	return (false);
}

/*
    renders single ray from player position
    into dirX and dirY
*/
void	render_ray(t_game *game, int size, int color)
{
	int			draw_start;
	t_vertex	pos;

	draw_start = 1;
	while (draw_start < size / 2)
	{
		pos.x = (game->player->posx * TILE_SIZE);
		pos.y = (game->player->posy * TILE_SIZE);
		if (valid_space(game, (pos.y + (draw_start * game->player->diry)) / TILE_SIZE,
				(pos.x + (draw_start * game->player->dirx)) / TILE_SIZE))
			mlx_put_pixel(game->img, (pos.x + (draw_start * game->player->dirx))
				/ 4, (pos.y + (draw_start * game->player->diry)) / 4, color);
		draw_start++;
	}
}

/*
    renders representation of 
    the player on the map 
    (prolly good to use a triangle)
*/
void	render_miniplay(t_game *game, int color)
{
	int	size;
	int	x;
	int	y;

	size = 12;
	x = -size / 2;
	while (x < size / 2)
	{
		y = -size / 2;
		while (y < size / 2)
		{
			if (game->player->posx + x > 0.0 && game->player->posx
				+ x < game->map->x_len * 1.0 && game->player->posy + y > 0.0
				&& game->player->posy + y < game->map->y_len * 1.0)
				mlx_put_pixel(game->img, (game->player->posx * TILE_SIZE + x)
					/ 4, (game->player->posy * TILE_SIZE + y) / 4, color);
			y++;
		}
		x++;
	}
	render_ray(game, 24, color);
}

void	cast_mapray(t_game *game, t_ray *ray)
{
	int		raycount;
	int		side;
	double	size;

	raycount = 0;
	ray->mapx = (int)game->player->posx;
	ray->mapy = (int)game->player->posy;
	while (raycount < 1)
	{
		calc_delta(ray);
		calc_side(game, ray);
		side = dda(game, ray);
		if (side == VERTICAL)
			size = (ray->side_dx - ray->d_distx);
		else
			size = ray->side_dy - ray->d_disty;
		render_ray(game, size / 2 * TILE_SIZE, RED);
		raycount++;
	}
}

/*
    render 2d map with player and 
    rays from player to walls (acc to FOV)
    this function will loop, so needs to 
    contain the raycasting bit 
*/
void	render_minimap(void *game_ptr)
{
	t_game	*game;
	t_ray	ray;

	game = (t_game *)game_ptr;
	ray.dirx = game->player->dirx;
	ray.diry = game->player->diry;
	clear_scene(game->img);
	cast_ray(game, &ray);
	render_map(game);
	render_miniplay(game, RED);
	cast_mapray(game, &ray);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   minimap_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/05 13:07:09 by adecheri       #+#    #+#                */
/*   Updated: 2026/03/05 13:07:12 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	toggle_minimap(t_game *game)
{
	if (game->map_img->enabled)
		game->map_img->enabled = false;
	else
		game->map_img->enabled = true;
}

//renders line at position.x from line.x until line.y in color
void	render_line(mlx_image_t *img, t_vertex line, t_vertex *position,
		int color)
{
	int	draw_start;
	int	draw_end;

	draw_start = line.x;
	draw_end = line.y;
	while (draw_start < draw_end)
	{
		mlx_put_pixel(img, position->x, draw_start, color);
		draw_start++;
	}
}

//renders a box from the
void	render_box(mlx_image_t *img, int y, int x, int color)
{
	int	offset;
	int	i;
	int	j;
	int	num;

	i = 0;
	j = 0;
	offset = 6;
	num = TILE_SIZE * MAPOFFSET;
	while (i < num)
	{
		j = 0;
		while (j < num)
		{
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/*
    render 2D map for the minimap
    with blue walls and white space 
*/
void	render_map(t_game *game)
{
	t_vertex	pos;

	pos.y = 0;
	while (pos.y < game->map->y_len)
	{
		pos.x = 0;
		while (pos.x < game->map->x_len)
		{
			if (game->map->grid[(int)floor(pos.y)][(int)floor(pos.x)] == WALL)
				render_box(game->img, (pos.y * TILE_SIZE) * MAPOFFSET, (pos.x
						* TILE_SIZE) * MAPOFFSET, BLUE);
			else
				render_box(game->img, (pos.y * TILE_SIZE) * MAPOFFSET, (pos.x
						* TILE_SIZE) * MAPOFFSET, WHITE);
			pos.x++;
		}
		pos.y++;
	}
}

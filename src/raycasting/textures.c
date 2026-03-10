/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/03/04 12:17:40 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void	draw_ceiling_floor(t_game *game, t_vertex line, int x)
{
	int	y;

	y = 0;
	while (y < line.x)
		mlx_put_pixel(game->img, x, y++, (game->map->ceiling << 8) | 0xFF);
	y = line.y;
	while (y < SCREEN_HEIGHT)
		mlx_put_pixel(game->img, x, y++, (game->map->floor << 8) | 0xFF);
}

void	draw_wall_strip(t_game *game, t_ray *ray, t_vertex line, int x)
{
	mlx_texture_t	*tex;
	double			tex_pos;
	int				tex_x;
	int				y;

	tex = pick_texture(game, ray);
	tex_x = get_tex_x(game, ray, tex);
	tex_pos = (line.x - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* ((double)tex->height / ray->line_height);
	y = line.x;
	while (y < line.y)
	{
		mlx_put_pixel(game->img, x, y, get_tex_pixel(tex, tex_x,
				ft_clamp((int)tex_pos, 0, tex->height - 1)));
		tex_pos += (double)tex->height / ray->line_height;
		y++;
	}
}

void	render_textured_line(t_game *game, t_ray *ray, t_vertex line,
		t_vertex *pos)
{
	draw_ceiling_floor(game, line, pos->x);
	draw_wall_strip(game, ray, line, pos->x);
}

int	get_tex_x(t_game *game, t_ray *ray, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == VERTICAL)
		wall_x = game->player->posy + ray->perp_walldist * ray->diry;
	else
		wall_x = game->player->posx + ray->perp_walldist * ray->dirx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == VERTICAL && ray->dirx > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == HORIZONTAL && ray->diry < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}



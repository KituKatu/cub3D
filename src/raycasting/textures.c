/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/03/03 12:53:13 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static mlx_texture_t	*pick_texture(t_game *game, t_ray *ray)
{
	if (ray->side == VERTICAL)
	{
		if (ray->dirx > 0)
			return (game->texture.east);
		else
			return (game->texture.west);
	}
	else if (ray->side == HORIZONTAL)
	{
		if (ray->diry > 0)
			return (game->texture.south);
		else
			return (game->texture.north);
	}
	return (game->texture.north);
}

static uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (0);
	pixel = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	render_textured_line(t_game *game, t_ray *ray, t_vertex line,
        t_vertex *pos)
{
    mlx_texture_t	*tex;
    double			wall_x;
    int				tex_x;
    int				tex_y;
    double			step;
    double			tex_pos;
    int				y;

    tex = pick_texture(game, ray);
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
    y = 0;
    while (y < line.x)
    {
        mlx_put_pixel(game->img, pos->x, y,
            (game->map->ceiling << 8) | 0xFF);
        y++;
    }
    step = (double)tex->height / ray->line_height;
    tex_pos = (line.x - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
    y = line.x;
    while (y < line.y)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        else if (tex_y >= (int)tex->height)
            tex_y = tex->height - 1;
        tex_pos += step;
        mlx_put_pixel(game->img, pos->x, y, get_tex_pixel(tex, tex_x, tex_y));
        y++;
    }
    while (y < SCREEN_HEIGHT)
    {
        mlx_put_pixel(game->img, pos->x, y,
            (game->map->floor << 8) | 0xFF);
        y++;
    }
}

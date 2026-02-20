/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/20 14:17:00 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static mlx_texture_t	*pick_texture(t_game *game, t_ray *ray)
{
	if (ray->side == VERTICAL)
	{
		if (ray->dirX > 0)
			return (game->texture.east);
		else
			return (game->texture.west);
	}
	else if (ray->side == HORIZONTAL)
	{
		if (ray->dirY > 0)
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

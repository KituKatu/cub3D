/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   texture_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/10 13:21:04 by adecheri       #+#    #+#                */
/*   Updated: 2026/03/10 13:21:06 by adecheri       ########   odam.nl        */
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

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

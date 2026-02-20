/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:42 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/20 13:59:22 by jmcgrane         ###   ########.fr       */
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
}


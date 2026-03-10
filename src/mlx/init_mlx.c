/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:29:43 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/03/04 12:41:17 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	wall_textures(t_game *game)
{
	game->texture.north = mlx_load_png(game->map->north);
	if (!game->texture.north)
		return (FAILURE);
	game->texture.south = mlx_load_png(game->map->south);
	if (!game->texture.south)
	{
		mlx_delete_texture(game->texture.north);
		return (FAILURE);
	}
	game->texture.east = mlx_load_png(game->map->east);
	if (!game->texture.east)
	{
		mlx_delete_texture(game->texture.north);
		mlx_delete_texture(game->texture.south);
		return (FAILURE);
	}
	game->texture.west = mlx_load_png(game->map->west);
	if (!game->texture.west)
	{
		mlx_delete_texture(game->texture.north);
		mlx_delete_texture(game->texture.south);
		mlx_delete_texture(game->texture.east);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	init_gamedetails(t_game *game)
{
	mlx_texture_t	*icon;

	icon = mlx_load_png("./textures/jmcgrane_S.png");
	if (!icon)
		ft_exit_errc("Failed to load icon", (void **)&game, 'g');
	mlx_set_icon(game->mlx, icon);
	mlx_delete_texture(icon);
	mlx_set_window_title(game->mlx, "Jack in the Box");
}

int	init_game(char *mapfile, t_game *game)
{
	mlx_image_t	*img;

	game->map = init_map(mapfile);
	if (!game->map)
		return (FAILURE);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (ft_exit_errc("Can't initilize mlx", (void **)&game, 'g'));
	if (wall_textures(game) == FAILURE)
		return (ft_exit_errc("Can't load wall texture", (void **)&game, 'g'));
	init_player(game);
	init_gamedetails(game);
	img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_exit_errc("Failed to load screen", (void **)&game, 'g');
	game->img = img;
	game->map_img = mlx_new_image(game->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!game->map_img || (mlx_image_to_window(game->mlx, game->map_img, 0,
				0) < 0))
		ft_exit_errc("Failed to load screen", (void **)&game, 'g');
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:29:43 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/01/28 16:19:59 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_image_t	*load_wall_texture(t_game *game, char *path)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
		return (NULL);
	return (img);
}

int	fill_img_array(t_game *game)
{
	game->map->img[0] = load_wall_texture(game, game->map->north);
	if (!game->map->img[0])
		return (FAILURE);
	game->map->img[1] = load_wall_texture(game, game->map->south);
	if (!game->map->img[1])
		return (FAILURE);
	game->map->img[2] = load_wall_texture(game, game->map->east);
	if (!game->map->img[2])
		return (FAILURE);
	game->map->img[3] = load_wall_texture(game, game->map->west);
	if (!game->map->img[3])
		return (FAILURE);
	return (SUCCESS);
}

int	init_game(char *mapfile)
{
	t_game	game;

	game.map = init_map(mapfile);
	if (!game.map)
		return (FAILURE);
	game.mlx = mlx_init(game.map->x_len * TILE_SIZE, game.map->y_len * TILE_SIZE, "Cub3D", false);
	if (!game.mlx)
		return (ft_exit_errc("Can't initilize mlx", (void *)&game, 'g'));
	if (fill_img_array(&game) == FAILURE)
		return (ft_exit_errc("Can't load wall texture", (void *)&game, 'w'));
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (SUCCESS);
}

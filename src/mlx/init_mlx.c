/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:29:43 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/18 12:46:43 by jmcgrane         ###   ########.fr       */
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

int	init_game(char *mapfile, t_game *game)
{
	mlx_image_t	*img;

	game->map = init_map(mapfile);
	if (!game->map)
		return (FAILURE);
	game->mlx = mlx_init(SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (ft_exit_errc("Can't initilize mlx", (void *)&game, 'g'));
	if (wall_textures(game) == FAILURE)
		return (ft_exit_errc("Can't load wall texture", (void *)&game, 'w'));
	init_player(game);
	img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_exit_errc("Failed to load screen", (void *)&game, 'g');
	game->img = img;
	render_map(game);
	return (SUCCESS);
}

// mlx_image_t	*load_wall_texture(t_game *game, char *path)
// {
// 	mlx_image_t		*img;
// 	mlx_texture_t	*texture;

// 	texture = mlx_load_png(path);
// 	if (!texture)
// 		return (NULL);
// 	img = mlx_texture_to_image(game->mlx, texture);
// 	mlx_delete_texture(texture);
// 	if (!img)
// 		return (NULL);
// 	return (img);
// }

// int	fill_img_array(t_game *game)
// {
// 	game->map->img[0] = load_wall_texture(game, game->map->north);
// 	if (!game->map->img[0])
// 		return (FAILURE);
// 	game->map->img[1] = load_wall_texture(game, game->map->south);
// 	if (!game->map->img[1])
// 		return (FAILURE);
// 	game->map->img[2] = load_wall_texture(game, game->map->east);
// 	if (!game->map->img[2])
// 		return (FAILURE);
// 	game->map->img[3] = load_wall_texture(game, game->map->west);
// 	if (!game->map->img[3])
// 		return (FAILURE);
// 	return (SUCCESS);
// }
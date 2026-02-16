/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:29:43 by jmcgrane          #+#    #+#             */
/*   Updated: 2026/02/13 12:48:41 by jmcgrane         ###   ########.fr       */
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

int	init_game(char *mapfile, t_game *game)
{
	mlx_image_t *img;

	game->map = init_map(mapfile);
	if (!game->map)
		return (FAILURE);
	game->mlx = mlx_init(SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (ft_exit_errc("Can't initilize mlx", (void *)&game, 'g'));
	if (fill_img_array(game) == FAILURE)
		return (ft_exit_errc("Can't load wall texture", (void *)&game, 'w'));
	init_player(game);

	img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_exit_errc("Failed to load screen", (void*)&game, 'g');
	game->img = img;
	render_map(game);
	return (SUCCESS);
}

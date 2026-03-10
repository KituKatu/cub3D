/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:13:00 by adecheri          #+#    #+#             */
/*   Updated: 2026/03/04 13:04:17 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
- The management of your window must remain smooth: changing to another window, minimizing, etc.
- Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West
- Your program must be able to set the floor and ceiling colors to two different ones.
*/
int	main(int ac, char **av)
{
	t_game	game;
	t_game	*gptr;

	if (ac != 2)
	{
		ft_exit_error("Wrong no of arguments\n");
		return (FAILURE);
	}
	init_game(av[1], &game);
	mlx_loop_hook(game.mlx, render_scene, (void *)&game);
	mlx_key_hook(game.mlx, cub_keyhook, (void*)&game);
	mlx_loop(game.mlx);
	gptr = &game;
	free_cubgame(&gptr);
	mlx_terminate(game.mlx);
	return (SUCCESS);
}

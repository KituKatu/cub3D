/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:13:00 by adecheri          #+#    #+#             */
/*   Updated: 2026/02/04 12:39:46 by jmcgrane         ###   ########.fr       */
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

	if (ac != 2)
	{
		ft_exit_error("Wrong no of arguments\n");
		return (FAILURE);
	}
	init_game(av[1], &game);
	mlx_loop_hook(game.mlx, render_minimap, (void*)&game);
	//mlx_loop_hook(game.mlx, render_scene, (void *)&game);
	mlx_key_hook(game.mlx, cub_keyhook, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (SUCCESS);
}

// // Add these constants
// # define SCREEN_WIDTH 1024
// # define SCREEN_HEIGHT 768

// // Player/raycasting structure
// typedef struct s_player
// {
//     double  pos_x;      // Player X position (in grid units, e.g., 5.5)
//     double  pos_y;      // Player Y position
//     double  dir_x;      // Direction vector X (-1 to 1)
//     double  dir_y;      // Direction vector Y (-1 to 1)
//     double  plane_x;    // Camera plane X (perpendicular to direction)
//     double  plane_y;    // Camera plane Y
// }   t_player;

// // Ray structure (for each column)
// typedef struct s_ray
// {
//     double  camera_x;    // X-coordinate on camera plane (-1 to 1)
//     double  dir_x;       // Ray direction X
//     double  dir_y;       // Ray direction Y
//     int     map_x;       // Current grid square X
//     int     map_y;       // Current grid square Y
//     double  side_dist_x; // Distance to next X gridline
//     double  side_dist_y; // Distance to next Y gridline
//     double  delta_dist_x;// Distance between X gridlines
//     double  delta_dist_y;// Distance between Y gridlines
//     double  perp_wall_dist;// Perpendicular distance to wall
//     int     step_x;      // Step direction (-1 or 1)
//     int     step_y;      // Step direction (-1 or 1)
//     int     hit;         // Was a wall hit?
//     int     side;        // Was it a NS or EW wall? (0 or 1)
//     int     line_height; // Height of wall slice to draw
//     int     draw_start;  // Where to start drawing
//     int     draw_end;    // Where to stop drawing
// }   t_ray;

// // Initialize player based on starting position and orientation
// void    init_player(t_game *game, t_player *player)
// {
//     player->pos_x = game->map->player_x + 0.5; // Center of tile
//     player->pos_y = game->map->player_y + 0.5;
    
//     // Set direction based on map orientation (N, S, E, W)
//     if (game->map->orient == 'N')
//     {
//         player->dir_x = 0;
//         player->dir_y = -1;
//         player->plane_x = 0.66; // FOV ~66 degrees
//         player->plane_y = 0;
//     }
//     else if (game->map->orient == 'S')
//     {
//         player->dir_x = 0;
//         player->dir_y = 1;
//         player->plane_x = -0.66;
//         player->plane_y = 0;
//     }
//     else if (game->map->orient == 'E')
//     {
//         player->dir_x = 1;
//         player->dir_y = 0;
//         player->plane_x = 0;
//         player->plane_y = 0.66;
//     }
//     else if (game->map->orient == 'W')
//     {
//         player->dir_x = -1;
//         player->dir_y = 0;
//         player->plane_x = 0;
//         player->plane_y = -0.66;
//     }
// }

// // Calculate ray direction for a given screen column
// void    init_ray(t_ray *ray, t_player *player, int x, int screen_width)
// {
//     // camera_x goes from -1 (left) to 1 (right)
//     ray->camera_x = 2 * x / (double)screen_width - 1;
//     ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
//     ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
//     ray->map_x = (int)player->pos_x;
//     ray->map_y = (int)player->pos_y;
//     ray->hit = 0;
// }

// // Calculate step and initial side distances
// void    calc_step_and_side_dist(t_ray *ray, t_player *player)
// {
//     // Avoid division by zero
//     ray->delta_dist_x = fabs(1 / ray->dir_x);
//     ray->delta_dist_y = fabs(1 / ray->dir_y);
    
//     if (ray->dir_x < 0)
//     {
//         ray->step_x = -1;
//         ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
//     }
//     else
//     {
//         ray->step_x = 1;
//         ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
//     }
//     if (ray->dir_y < 0)
//     {
//         ray->step_y = -1;
//         ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
//     }
//     else
//     {
//         ray->step_y = 1;
//         ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
//     }
// }

// // DDA algorithm - step through the grid until we hit a wall
// void    perform_dda(t_ray *ray, t_map *map)
// {
//     while (ray->hit == 0)
//     {
//         // Jump to next grid square (either X or Y direction)
//         if (ray->side_dist_x < ray->side_dist_y)
//         {
//             ray->side_dist_x += ray->delta_dist_x;
//             ray->map_x += ray->step_x;
//             ray->side = 0; // East-West wall
//         }
//         else
//         {
//             ray->side_dist_y += ray->delta_dist_y;
//             ray->map_y += ray->step_y;
//             ray->side = 1; // North-South wall
//         }
//         // Check if ray hit a wall
//         if (map->grid[ray->map_y][ray->map_x] == WALL)
//             ray->hit = 1;
//     }
// }

// // Calculate wall height and draw positions
// void    calc_wall_height(t_ray *ray, int screen_height)
// {
//     // Calculate perpendicular distance (avoids fisheye effect)
//     if (ray->side == 0)
//         ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
//     else
//         ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
    
//     // Calculate line height
//     ray->line_height = (int)(screen_height / ray->perp_wall_dist);
    
//     // Calculate start and end of wall slice
//     ray->draw_start = -ray->line_height / 2 + screen_height / 2;
//     if (ray->draw_start < 0)
//         ray->draw_start = 0;
//     ray->draw_end = ray->line_height / 2 + screen_height / 2;
//     if (ray->draw_end >= screen_height)
//         ray->draw_end = screen_height - 1;
// }

// // Main raycasting loop - call this each frame
// void    raycast(t_game *game, t_player *player)
// {
//     t_ray   ray;
//     int     x;

//     x = 0;
//     while (x < SCREEN_WIDTH)
//     {
//         init_ray(&ray, player, x, SCREEN_WIDTH);
//         calc_step_and_side_dist(&ray, player);
//         perform_dda(&ray, game->map);
//         calc_wall_height(&ray, SCREEN_HEIGHT);
//         // TODO: draw_wall_slice(game, &ray, x);
//         x++;
//     }
// }
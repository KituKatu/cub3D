/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mouse_input.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/02 14:46:26 by adecheri       #+#    #+#                */
/*   Updated: 2026/03/02 14:46:28 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* checks if mouse pos is at the left or right 
    side of the screen and rotates accordingly
*/
t_vertex	check_mouse(t_game *game)
{
	int32_t		mx;
	int32_t		my;
	t_vertex	mouse_pos;

	mx = 0;
	my = 0;
	mlx_get_mouse_pos(game->mlx, &mx, &my);
	mouse_pos.x = mx;
	mouse_pos.y = my;
	return (mouse_pos);
}

//have the direction reset when mouse is not moving
void	mouse_reset(t_game *game)
{
	int32_t	mx;
	int32_t	my;

	mlx_get_mouse_pos(game->mlx, &mx, &my);
	game->player->dirx = game->player->dirx;
	game->player->diry = game->player->diry;
	game->player->plane_x = game->player->plane_x;
	game->player->plane_y = game->player->plane_y;
}

/* have the mouse position rotate the camera
    at the left and right part of the screen
    the mouse pos will reset to the middle
*/
void	mouse_rot(t_game *game, t_vertex m_pos)
{
	t_vertex	new_pos;
	double		angle;

	new_pos = check_mouse(game);
	angle = new_pos.x - m_pos.x;
	if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x > SCREEN_WIDTH
		|| new_pos.y > SCREEN_HEIGHT)
		return ;
	else if (new_pos.x > 0 && new_pos.x < SCREEN_WIDTH)
	{
		if (angle == 0.00)
			mouse_reset(game);
		else if (new_pos.x < SCREEN_WIDTH / 2 || new_pos.x > SCREEN_WIDTH/2)
		{
			rot_camera(game, angle * DEGREE);
			if (new_pos.x < (SCREEN_WIDTH * 0.1) || new_pos.x > (SCREEN_WIDTH * 0.9))
				mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, new_pos.y);
		}
	}
}

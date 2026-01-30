/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   raycasting.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/16 16:38:38 by adecheri       #+#    #+#                */
/*   Updated: 2026/01/16 16:38:40 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <time.h>

/*calculate height of walls on grid by raycasting
    calc vector of camera plane?
    direction vector multiplies the pos of player in cert direction (length doesn't matter only dir)
    load in vector lib?
*/

//calculate distance ray to wall 



//need function to handle rotation
void rotate_c(t_game **game, char direct)
{
    t_player *play;
    double oldDirX;
    double oldPlaneX;

    play = (*game)->player;
    oldDirX = play->dirX;
    oldPlaneX = play->planeX;
    if (direct == 'l')
    {
        play->dirX = play->dirX * cos(ROTSPEED) - play->dirY * sin(ROTSPEED);
        play->dirY = oldDirX * sin(ROTSPEED) + play->dirY * cos(ROTSPEED);
        play->planeX = play->planeX * cos(ROTSPEED) - play->planeY * sin(ROTSPEED);
        play->planeY = oldPlaneX * sin(ROTSPEED) + play->planeY * cos(ROTSPEED);
    }
    else if (direct == 'r')
    { 
        play->dirX = play->dirX * cos(-ROTSPEED) - play->dirY * sin(-ROTSPEED);
        play->dirY = oldDirX * sin(-ROTSPEED) + play->dirY * cos(-ROTSPEED);
        play->planeX = play->planeX * cos(-ROTSPEED) - play->planeY * sin(-ROTSPEED);
        play->planeY = oldPlaneX * sin(-ROTSPEED) + play->planeY * cos(-ROTSPEED);
    }
}

void move_pl(t_game **game, double stepY, double stepX)
{

}


//need a keyhook where the pos of player is updated 
void	cub_keyhook(mlx_key_data_t keydown, void *param)
{
	if (map->fd < 0)
		ft_exit_errc("Error opening file", NULL, '0');
	//needs while loop until EOF 
	t_game	**game;

	game = param;
	if (keydown.action == MLX_PRESS || keydown.action == MLX_REPEAT)
	{
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window((*game)->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_pl(game, -1, 0);
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_pl(game, 1, 0);
		if (keydown.key == MLX_KEY_LEFT || keydown.key == MLX_KEY_A)
			rotate_c(game, 'l', );
		if (keydown.key == MLX_KEY_RIGHT || keydown.key == MLX_KEY_D)
			rotate_c(game, 'r');
	}
}

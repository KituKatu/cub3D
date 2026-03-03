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


double dot(t_vertex a, t_vertex b)
{
    return (a.x*b.x + a.y*b.y);
}

t_vertex cross(t_vertex a, t_vertex b)
{
    t_vertex result;

    result.x = a.y*b.z - a.z*b.y;
    result.y = a.z*b.x - a.x*b.z;
    result.z = a.x*b.y - a.y*b.x;
    return (result);
}

t_vertex scale(t_vertex v, double s) 
{
    t_vertex result;

    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    return (result);
}


t_vertex add(t_vertex a, t_vertex b)
{
    t_vertex result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return (result);
}

t_vertex rodr_rot(t_vertex vec_v, t_vertex vec_k, double theta)
{
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);

    t_vertex term1 = scale(vec_v, cos_theta);

    t_vertex k_cross_v = cross(vec_k, vec_v);
    t_vertex term2 = scale(k_cross_v, sin_theta);

    double k_dot_v = dot(vec_k, vec_v);
    t_vertex term3 = scale(vec_k, k_dot_v * (1.0 - cos_theta));

    return add(add(term1, term2), term3);
}




/* checks if mouse pos is at the left or right 
    side of the screen and rotates accordingly
*/
t_vertex check_mouse(t_game *game)
{
    int32_t mx;
    int32_t my;

    mx = 0;
    my = 0;
    t_vertex mouse_pos;

    mlx_get_mouse_pos(game->mlx, &mx, &my);
    mouse_pos.x = mx;
    mouse_pos.y = my; 
    return (mouse_pos);
}

//have the direction reset when mouse is not moving
void mouse_reset(t_game *game)
{
    game->player->dirX = game->player->dirX;
    game->player->dirY = game->player->dirY;
}


/* rotate the camera according to the mouse 
    movement on the screen
*/
void mouse_rot(t_game *game, t_vertex m_pos)
{
    t_vertex new_pos;

    new_pos = check_mouse(game);
    
    if (new_pos.x < 0 || new_pos.y < 0)
        return;
    else if (new_pos.x > SCREEN_WIDTH || new_pos.y > SCREEN_HEIGHT)
        return ;
    else if (new_pos.x > 0 && new_pos.x < SCREEN_WIDTH)
    {
        t_vertex rotated;
        t_vertex v;
        v.x = game->player->dirX;
        v.y = game->player->dirY;
        v.z = 0;
        t_vertex axis = {0.0, 0.0, 1.0};
        double angle;

        angle = (new_pos.x - m_pos.x) *DEGREE; 
        if (angle == 0.00)
        {
            mouse_reset(game);
            return ;
        }
        rotated = rodr_rot(v, axis, angle);
        game->player->dirX = rotated.x;
        game->player->dirY = rotated.y;
        printf("ROT = (%f, %f, %f)\n", rotated.x, rotated.y, rotated.z);

    }
}
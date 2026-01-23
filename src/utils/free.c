/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   free.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/16 16:39:35 by adecheri       #+#    #+#                */
/*   Updated: 2026/01/16 16:39:36 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"



void free_cubmap(t_map **map)
{
    int i;

    i = 0;
    ft_safefree((*map)->mapline);
    ft_safefree((*map)->north);
    ft_safefree((*map)->east);
    ft_safefree((*map)->south);
    ft_safefree((*map)->west);
    while((*map)->grid)
    {
        ft_safefree((*map)->grid[i]);
        i++;
    }
}

void ft_clean_cubed(void **ptr, char id)
{
    if (id == 'm')
        free_cubmap((t_map **)ptr);
    else
        ft_safefree(ptr);
}
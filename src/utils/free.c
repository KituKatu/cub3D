/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:39:35 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/26 16:55:38 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"



void free_cubmap(t_map **map)
{
    int i;

    i = 0;
    ft_safefree((void*)&(*map)->line);
    ft_safefree((void*)&(*map)->north);
    ft_safefree((void*)&(*map)->east);
    ft_safefree((void*)&(*map)->south);
    ft_safefree((void*)&(*map)->west);
    while((*map)->grid)
    {
        ft_safefree((void*)&(*map)->grid[i]);
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
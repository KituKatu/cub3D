/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:26:14 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/26 17:00:03 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//parses colors read 
int parse_color(char *line, t_map *map)
{
    char c_arr[3];
    int color[3];
    char *ptr;
    int i;

    c_arr[3]= NULL;
    i = 0; 
    ptr = line;
    while (*ptr)
    {
        if (ft_isdigit(*ptr) || *ptr == ',')
            ptr++;
        else 
            ft_exit_errc("Wrong input colors", (void*)&map, 'm');
    }
    *c_arr = ft_split(line, ',');
    while (c_arr[i])
    {
        color[i] = ft_atoi(c_arr[i])%255;
        ft_safefree(c_arr[i]);
        i++;
    }
    // Combine into single int: 0xRRGGBB
    return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

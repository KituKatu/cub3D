/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:26:14 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/28 13:17:03 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_color_chars(char *line, t_map *map)
{
    char	*ptr;

    ptr = line;
    while (*ptr)
    {
        if (ft_isdigit(*ptr) || *ptr == ',')
            ptr++;
        else
            ft_exit_errc("Wrong input colors", (void *)&map, 'm');
    }
}

void	color_error(char **c_arr, char *msg, t_map *map)
{
    ft_freearr((void **)c_arr);
    ft_exit_errc(msg, (void *)&map, 'm');
}

void	extract_color_values(char **c_arr, int *color, t_map *map)
{
    int	i;
    int	val;

    i = 0;
    while (c_arr[i])
    {
        val = ft_atoi(c_arr[i]);
        if (val < 0 || val > 255)
            color_error(c_arr, "Color value out of range", map);
        color[i] = val;
        i++;
        if (i > 3)
            color_error(c_arr, "Too many color components", map);
    }
    if (i != 3)
        color_error(c_arr, "Invalid color format", map);
}

int	parse_color(char *line, t_map *map)
{
    char	**c_arr;
    int		color[3];

    validate_color_chars(line, map);
    c_arr = ft_split(line, ',');
    if (!c_arr)
        ft_exit_errc("Colors split failed", (void *)&map, 'm');
    extract_color_values(c_arr, color, map);
    ft_freearr((void **)c_arr);
    ft_safefree((void **)&line);
    return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

// int parse_color(char *line, t_map *map)
// {
// 	char	**c_arr;
// 	int		color[3];
// 	char	*ptr;
// 	int		i;
// 	int		val;

//     i = 0;
//     ptr = line;
//     while (*ptr)
//     {
//         if (ft_isdigit(*ptr) || *ptr == ',')
//             ptr++;
//         else
//             ft_exit_errc("Wrong input colors", (void*)&map, 'm');
//     }
//     c_arr = ft_split(line, ',');
//     if (!c_arr)
//         ft_exit_errc("Colors split failed", (void*)&map, 'm');
//     while (c_arr[i])
//     {
//         val = ft_atoi(c_arr[i]);
//         if (val < 0 || val > 255)
//         {
//             ft_freearr((void**)c_arr);
//             ft_exit_errc("Color value out of range", (void*)&map, 'm');
//         }
//         color[i] = val;
//         i++;
//         if (i > 3)
//         {
//             ft_freearr((void**)c_arr);
//             ft_exit_errc("Too many color components", (void*)&map, 'm');
//         }
//     }
//     if (i != 3)
//     {
//         ft_freearr((void**)c_arr);
//         ft_exit_errc("Invalid color format", (void*)&map, 'm');
//     }
//     ft_freearr((void**)c_arr);
//     ft_safefree((void**)&line);
//     return ((color[0] << 16) | (color[1] << 8) | color[2]);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:12 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/23 12:56:12 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../lib/libft/libft.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define SPACE '0'
# define WALL '1'
# define READ_SIZE 42



typedef struct s_game
{
    mlx_t *mlx;
    
} t_game;


typedef struct s_map
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			fd;
	int			x_len;
	int			y_len;
	char		*mapline;
	char		**mapgrid;
	char		orient;
	int			floor;
	int			ceiling;
	mlx_image_t	*imgs[5];
}				t_map;



/*Map Validation*/

int		dot_cub(char *file);
int		empty_line(char *line);
t_map	*init_map(char *mapname);
int		init_game(char *mapfile);
int		read_map(char *mapname, t_map *map);
void	parse_identifier(char *line, t_map *map);

/*Key Hooks*/


/*Error Functions*/

void ft_clean_cubed(void **ptr);
int ft_exit_errc(const char *msg, void **ptr);


#endif
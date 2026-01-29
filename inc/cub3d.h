/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:12 by adecheri          #+#    #+#             */
/*   Updated: 2026/01/28 16:19:32 by jmcgrane         ###   ########.fr       */
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

# define WALL '1'
# define SPACE '0'
# define SUCCESS 0
# define FAILURE 1
# define READ_SIZE 42
# define TILE_SIZE 32

typedef struct s_map
{
	int			fd;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			x_len;
	int			y_len;
	char		*line;
	char		*name;
	int			floor;
	char		**grid;
	char		orient;
	int			ceiling;
	mlx_image_t	*img[4];
}				t_map;

typedef struct s_game
{
	mlx_t	*mlx;
	t_map	*map;
}			t_game;

/*Map Validation*/

int		dot_cub(char *file);
int		read_map(t_map *map);
bool	frst_last(char *line);
void	map_setup(t_map *map);
void	parse_map(t_map *map);
int		empty_line(char *line);
char	**init_grid(t_map *map);
t_map	*init_map(char *mapname);
int		init_game(char *mapfile);
int		parse_map_id(char *line);
int		read_map_again(t_map *map);
void	map_dimensions(t_map *map);
void	create_grid(t_map *map, int i, int j);
int		parse_identifier(char *line, t_map *map);

/*Map colors*/

int		parse_color(char *line, t_map *map);
void	validate_color_chars(char *line, t_map *map);
void	color_error(char **c_arr, char *msg, t_map *map);
void	extract_color_values(char **c_arr, int *color, t_map *map);

/*MLX*/

int			fill_img_array(t_game *game);
mlx_image_t	*load_wall_texture(t_game *game, char *path);

/*Key Hooks*/

/*Error Functions*/

void	ft_clean_cubed(void **ptr, char id);
int		ft_exit_errc(const char *msg, void **ptr, char id);


#endif
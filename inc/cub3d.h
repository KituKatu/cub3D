/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:12 by adecheri          #+#    #+#             */
/*   Updated: 2026/03/10 13:55:14 by jmcgrane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <../lib/libft/libft.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WALL '1'
# define SPACE '0'
# define SUCCESS 0
# define FAILURE 1
# define MAP_START 2
# define VERTICAL 0
# define HORIZONTAL 1
# define READ_SIZE 42
# define MAPOFFSET 0.25
# define DEGREE 0.01745
# define PI 3.14159
# define MOVSPEED 3.0 //0.8
# define ROTSPEED 3.0 //0.5235 //0.26179
# define WHITE 0xFFFFFFFF
# define BLUE 111184
# define RED 0xFF033E
# define YELLOW 0xFFFF00

# define TILE_SIZE 64
# define FOV 0.66          // Same as wolfenstien
# define SCREEN_WIDTH 2048 // Standard (4 : 3 aspect ratio)
# define SCREEN_HEIGHT 1436

typedef struct s_vars
{
	int		x;
	int		y;
	char	**copy;
	int		result;
}			t_vars;

typedef struct s_vertex
{
	double			x;
	double			y;
}					t_vertex;

typedef struct s_map
{
	int				fd;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	int				x_len;
	int				y_len;
	char			*line;
	char			*name;
	int				floor;
	char			**grid;
	char			orient;
	int				ceiling;
	int				player_x;
	int				player_y;
	int				floor_check;
	int				ceiling_check;
	mlx_image_t		*img[4];
}					t_map;

typedef struct s_ray
{
	double			stepx;
	double			stepy;
	double			dirx;
	double			diry;
	double			mapx;
	double			mapy;
	double			side_dx;
	double			side_dy;
	double			d_distx;
	double			d_disty;
	double			perp_walldist;
	double			wallx;
	int				line_height;
	int				side;
}					t_ray;

typedef struct s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			plane_x;
	double			plane_y;
	bool			moving;
}					t_player;

typedef struct s_minimap
{
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*player;
}					t_minimap;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}					t_texture;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*map_img;
	t_map			*map;
	t_player		*player;
	t_minimap		minimap;
	t_texture		texture;
}					t_game;

/*Map Validation*/

int		dot_cub(char *file);
int		read_map(t_map *map);
bool	frst_last(char *line);
void	map_setup(t_map *map);
char	**map_copy(t_map *map);
int		empty_line(char *line);
int		one_player(t_map *map);
char	**init_grid(t_map *map);
t_map	*init_map(char *mapname);
int		parse_map_id(char *line);
int		validate_map(t_map *map);
int		is_valid_char(t_map *map);
int		read_map_again(t_map *map);
void	map_dimensions(t_map *map);
int		wall_textures(t_game *game);
int		n_s_e_w(t_map *map, char *line);
void	parse_map_first_line(t_map *map);
int		east_path(t_map *map, char *line);
int		west_path(t_map *map, char *line);
int		north_path(t_map *map, char *line);
int		south_path(t_map *map, char *line);
int		is_valid_map(t_map *map, char *line);
int		floor_ceiling(t_map *map, char *line);
void	create_grid(t_map *map, int i, int j);
int		init_game(char *mapfile, t_game *game);
int		parse_identifier(char *line, t_map *map);
int		floodfill(t_map *map, char **map_copy, int x, int y);
int		read_map_helper(t_map *map);

/*Map colors*/

int					parse_color(char *line, t_map *map);
void				validate_color_chars(char *line, t_map *map);
void				color_error(char **c_arr, char *msg, t_map *map);
void				extract_color_values(char **c_arr, int *color, t_map *map);
uint32_t			get_tex_pixel(mlx_texture_t *tex, int x, int y);
mlx_texture_t		*pick_texture(t_game *game, t_ray *ray);

/*MLX*/

int					fill_img_array(t_game *game);
mlx_image_t			*load_wall_texture(t_game *game, char *path);

/*Key Hooks*/

void				cub_keyhook(mlx_key_data_t keydown, void *param);

/*Error Functions*/

void				ft_clean_cubed(void **ptr, char id);
int					ft_exit_errc(const char *msg, void **ptr, char id);
void				free_cubgame(t_game **game);

/*Ray Casting*/

bool				dda(t_game *game, t_ray *ray);
void				init_player(t_game *game);
void				calc_side(t_game *game, t_ray *ray);
void				rot_camera(t_game *game, double speed);
void				calc_delta(t_ray *ray);
void				calc_walldist(t_game *game, t_ray *ray, int side);
t_vertex			calc_height(t_ray *ray);
void				init_orient_n_s(t_game *game, t_player *player);
void				init_orient_e_w(t_game *game, t_player *player);
void				mouse_rot(t_game *game, t_vertex m_pos);
t_vertex			check_mouse(t_game *game);
void				move_fb(t_game *game, t_vertex pos, keys_t dir,
						double speed);
void				move_lr(t_game *game, t_vertex pos, keys_t dir,
						double speed);
void				cast_mapray(t_game *game, t_ray *ray);
void				cast_ray(t_game *game, t_ray *ray);
void				render_textured_line(t_game *game, t_ray *ray,
						t_vertex line, t_vertex *pos);

/*Rendering*/

void				clear_scene(mlx_image_t *img);
void				render_line(mlx_image_t *img, t_vertex line,
						t_vertex *position, int color);
void				render_scene(void *game);
void				render_map(t_game *game);
void				render_minimap(void *game_ptr);
void				render_miniplay(t_game *game, int color);
void				render_ray(t_game *game, int size, int color);
int					get_tex_x(t_game *game, t_ray *ray, mlx_texture_t *tex);
void				render_textured_line(t_game *game, t_ray *ray,
						t_vertex line, t_vertex *pos);
void				toggle_minimap(t_game *game);
void				draw_wall_strip(t_game *game, t_ray *ray, t_vertex line,
						int x);
void				draw_ceiling_floor(t_game *game, t_vertex line, int x);
int					ft_clamp(int value, int min, int max);

#endif
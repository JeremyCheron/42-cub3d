/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:36:16 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/03 12:51:54 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/include/libft.h"
# include "../minilibx/mlx42.h"
# include <fcntl.h>
# include <math.h>

// Configuration constants
# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT 1080
# define PI 3.14159265358979

// Game constants
# define ANGLE_SPEED 0.1
# define BLOCK_SIZE 64
# define PLAYER_SPEED 20
# define ROTATION_SPEED 0.05

typedef struct s_config
{
	char    *north_texture;
	char    *south_texture;
	char    *east_texture;
	char    *west_texture;
} t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_game
{
	mlx_t           *mlx;
	void            *win;
	mlx_image_t     *image_global;
	t_player        player;
	t_config        config;
	char            **map;
	mlx_texture_t   *texture_north;
	mlx_texture_t   *texture_south;
	mlx_texture_t   *texture_east;
	mlx_texture_t   *texture_west;
} t_game;


// void init_game(t_game *game);
int			init_textures(t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
char ** get_map(void);
int			get_rgba(int r, int g, int b, int a);
void	handle_input(mlx_key_data_t keydata, void *param);
void init_player(t_player *player);
void draw_loop(void *param);












// Map elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'

// Error messages
# define ERR_MAP_EXT "Error\nInvalid map extension (must be .ber)\n"
# define ERR_MAP_EMPTY "Error\nEmpty map\n"
# define ERR_MAP_RECT "Error\nMap must be rectangular\n"
# define ERR_MAP_WALLS "Error\nMap must be surrounded by walls\n"
# define ERR_MAP_CHARS "Error\nInvalid character in map\n"
# define ERR_MAP_MISSING "Error\nMissing elements in map\n"
# define ERR_INIT_MLX "Error\nFailed to initialize MLX\n"
# define ERR_LOAD_TEXTURES "Error\nFailed to load textures\n"
# define ERR_PARSE_MAP "Error\nFailed to parse map\n"
# define ERR_MAP_IMPOSSIBLE "Error\nMap is not solvable\n"
# define ERR_MAP_SIZE "Error\nMap dimensions are invalid\n"

// Initialization functions
// int			allocate_grid(t_map *map);

// // Map handling functions
// int			check_map_extension(char *filename);
// int			parse_map(t_game *game, char *map_path);
// void		free_map(t_map *map);
// int			validate_map(t_map *map);
// int			check_map_elements(t_map *map);
// int			check_map_walls(t_map *map);
//
// // Map validation functions
// int			is_map_solvable(t_map *map);
// char		**duplicate_grid(t_map *map);
//
// // Game mechanics functions
// void		rotate_player_x(t_game *game, float angle);
// void		move_player(t_game *game, float dx, float dy);
// // void		handle_input(mlx_key_data_t keydata, void *param);
// void		render_map(t_game *game);
// void		cleanup_game(t_game *game);


char	**read_map(
			const char *filename);

void	error_exit(
			char *message);

#endif

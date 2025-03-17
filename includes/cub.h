/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:36:16 by jcheron           #+#    #+#             */
/*   Updated: 2025/03/13 11:04:34 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/include/libft.h"
# include "../minilibx/mlx42.h"
# include <fcntl.h>
# include <math.h>
# include "messages.h"
# include "parser.h"

// Configuration constants
# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT 1080
# define PI 3.14159265358979

// Game constants
# define ANGLE_SPEED 0.1
# define BLOCK_SIZE 64
# define PLAYER_SPEED 20

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image_global;
	t_player		player;
	t_config		config;
	char			**map;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_east;
	mlx_texture_t	*texture_west;
}	t_game;

bool		init_game(t_game *game);
int			get_rgba(int r, int g, int b, int a);
void		handle_input(mlx_key_data_t keydata, void *param);
void		draw_loop(void *param);
char		**read_map(const char *filename, t_game *game);
void		error_exit(char *arg, char *message);
int			parse_file(char *filename, t_game *game);
void		process_config_line(t_game *game, char *line);
void		process_map_line(t_game *game, char *line, int y);
int			parse_color(char *line, int color[3]);
int			set_texture(char **texture, char *line);
char		**append_line_to_map(char **map, char *line);

#endif

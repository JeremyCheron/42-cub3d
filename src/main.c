/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/21 07:47:04 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../includes/render.h"
#include "../includes/player.h"

static void	init_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->east_texture = NULL;
	config->west_texture = NULL;
	config->floor_color[0] = -1;
	config->floor_color[1] = -1;
	config->floor_color[2] = -1;
	config->ceiling_color[0] = -1;
	config->ceiling_color[1] = -1;
	config->ceiling_color[2] = -1;
}

// static void	init_game_struct(t_game *game)
// {
// 	game->mlx = NULL;
// 	game->image_global = NULL;
// 	init_config(&game->config);
// 	game->map = NULL;
// 	game->texture_north = NULL;
// 	game->texture_south = NULL;
// 	game->texture_east = NULL;
// 	game->texture_west = NULL;
// }

static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, handle_input, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit(argv[0], "Usage: ./cub3D <map.cub>");
	init_config(&game.config);
	read_map(argv[1], &game);
	if (!validate_map(&game))
	{
		ft_putendl_fd("Error\nInvalid map", 2);
		clear_config(&game.config);
		free_map(game.map);
		return (1);
	}
	if (!init_game(&game))
	{
		ft_putendl_fd("Error\nFailed to initialize game", 2);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	clear_game(&game);
	return (0);
}
